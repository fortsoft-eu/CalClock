/**
 * This is open-source software licensed under the terms of the MIT License.
 *
 * Copyright (c) 2026 Petr Červinka - FortSoft <cervinka@fortsoft.eu>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **
 * Last modified for version 1.7.2.5
 */

#pragma once

#include <windows.h>

struct PrintJob;
class PrintSettings;
class ModernPrintDialog;

#if _WIN32_WINNT >= 0x0A00

#include "PrintSettings.h"
#include <windows.graphics.printing.h>
#include <DocumentSource.h>
#include <PrintPreview.h>
#include <d2d1_1.h>
#include <d3d11.h>
#include <dwrite.h>
#include <wrl/client.h>

namespace Printing = ABI::Windows::Graphics::Printing;
namespace Foundation = ABI::Windows::Foundation;

typedef Foundation::ITypedEventHandler<Printing::PrintManager*,
    Printing::PrintTaskRequestedEventArgs*> PrintRequestedHandler;
typedef Foundation::ITypedEventHandler<Printing::PrintTask*,
    Printing::PrintTaskCompletedEventArgs*> PrintCompletedHandler;
typedef Foundation::IAsyncOperation<bool> PrintUiOperation;
typedef Foundation::IAsyncOperationCompletedHandler<bool> PrintUiCompletedHandler;

/// Identifies the captured text range assigned to one printed page.
struct ModernPrintPage {
    UINT32 start;
    UINT32 length;
};

/// Owns the modern Windows print UI, task callbacks and pagination of an immutable text snapshot.
class ModernPrintDialog : public Printing::IPrintDocumentSource, public IPrintDocumentPageSource,
    public IPrintPreviewPageCollection, public PrintRequestedHandler,
    public Printing::IPrintTaskSourceRequestedHandler, public PrintCompletedHandler,
    public PrintUiCompletedHandler {

private:
    LONG references;
    volatile LONG canceled;
    CRITICAL_SECTION lock;
    PrintJob* job;
    DEVMODEW deviceMode;
    ModernPrintPage* pages;
    UINT pageCount;
    UINT completeMessage;
    D2D1_RECT_F content;
    Printing::PrintPageDescription description;
    Microsoft::WRL::ComPtr<IUnknown> marshaler;
    Microsoft::WRL::ComPtr<Printing::IPrintManager> manager;
    Microsoft::WRL::ComPtr<Printing::IPrintTask> task;
    Microsoft::WRL::ComPtr<PrintUiOperation> operation;
    Microsoft::WRL::ComPtr<IPrintPreviewDxgiPackageTarget> preview;
    Microsoft::WRL::ComPtr<IPrintDocumentPackageTarget> document;
    Microsoft::WRL::ComPtr<ID2D1Factory1> factory;
    Microsoft::WRL::ComPtr<ID3D11Device> graphics;
    Microsoft::WRL::ComPtr<ID2D1Device> device;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext> context;
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> ink;
    Microsoft::WRL::ComPtr<IDWriteFactory> textFactory;
    Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormat;
    EventRegistrationToken requestedToken;
    EventRegistrationToken completedToken;
    bool requested;
    bool completed;
    bool apartment;
    bool notified;
    bool failed;

    /// Creates the software graphics device, Direct2D context and DirectWrite text resources.
    HRESULT InitializeGraphics();

    /// Matches the captured edit font and retains its size in device-independent units.
    HRESULT InitializeTextFormat();

    /// Groups complete DirectWrite lines into pages within the current printable area.
    HRESULT BuildPages();

    /// Rebuilds pagination from the selected paper size, printable area, margins and edit font.
    HRESULT Prepare(IInspectable* options);

    /// Records one zero-based document page as text glyphs in a Direct2D command list.
    HRESULT CreatePage(UINT page, ID2D1CommandList** result);

    /// Records the result and posts at most one completion message with its own source reference.
    void Complete(bool failure);

    /// Applies the stored paper size and orientation to the system print task options.
    void ApplySettings(Printing::IPrintTaskOptionsCore* options) const;

    /// Uses the heap storage already allocated by Create without a C runtime allocation.
    static void* operator new(size_t size, void* memory);

    /// Frees class storage from the process heap for the compiler's deleting destructors.
    static void operator delete(void* memory);

public:
    /// Adopts the print snapshot and copies the initial printer settings and completion message.
    ModernPrintDialog(PrintJob* snapshot, const PrintSettings& settings, UINT completionMessage);

    /// Releases the captured report, page ranges and owned graphics resources.
    ~ModernPrintDialog();

    /// Adopts the snapshot and caller-selected completion message, or returns null on allocation failure.
    static ModernPrintDialog* Create(PrintJob* snapshot, const PrintSettings& settings,
            UINT completionMessage);

    /// Registers the print callbacks and asynchronously opens the system print UI for the owner window.
    HRESULT Show(HWND owner);

    /// Stops pending work, removes event handlers and reports any recorded printing failure.
    bool Close();

    /// Exposes the document, preview, event callback and marshaling interfaces of this source.
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID id, void** result) override;

    /// Retains one COM reference to the print source.
    ULONG STDMETHODCALLTYPE AddRef() override;

    /// Releases one COM reference and destroys the source when no references remain.
    ULONG STDMETHODCALLTYPE Release() override;

    /// Allocates the list of inspectable interface identifiers returned to the caller.
    HRESULT STDMETHODCALLTYPE GetIids(ULONG* count, IID** ids) override;

    /// Returns the Windows Runtime class name of the document source.
    HRESULT STDMETHODCALLTYPE GetRuntimeClassName(HSTRING* name) override;

    /// Returns the base trust level used by the document source.
    HRESULT STDMETHODCALLTYPE GetTrustLevel(TrustLevel* trust) override;

    /// Creates the system print task and applies the captured page settings.
    HRESULT STDMETHODCALLTYPE Invoke(Printing::IPrintManager* sender,
        Printing::IPrintTaskRequestedEventArgs* args) override;

    /// Supplies the captured document source when Windows requests printable content.
    HRESULT STDMETHODCALLTYPE Invoke(Printing::IPrintTaskSourceRequestedArgs* args) override;

    /// Reports the system print task result to the owning window.
    HRESULT STDMETHODCALLTYPE Invoke(Printing::IPrintTask* sender,
        Printing::IPrintTaskCompletedEventArgs* args) override;

    /// Completes the request if showing the system print UI fails or is canceled.
    HRESULT STDMETHODCALLTYPE Invoke(PrintUiOperation* sender, Foundation::AsyncStatus status) override;

    /// Connects the system preview target and returns this source's preview page collection.
    HRESULT STDMETHODCALLTYPE GetPreviewPageCollection(IPrintDocumentPackageTarget* target,
        IPrintPreviewPageCollection** collection) override;

    /// Recalculates the layout for changed print options and publishes the final page count.
    HRESULT STDMETHODCALLTYPE Paginate(UINT32 currentPage, IInspectable* options) override;

    /// Renders the requested one-based page to a DXGI surface for the system preview.
    HRESULT STDMETHODCALLTYPE MakePage(UINT32 page, FLOAT width, FLOAT height) override;

    /// Writes all final pages to the system package target and cancels the package on failure.
    HRESULT STDMETHODCALLTYPE MakeDocument(IInspectable* options, IPrintDocumentPackageTarget* target)
        override;
};

#endif

/// Selects the modern printing path for Windows 11 system builds.
bool UseModernPrintDialog();

/// Adopts the snapshot and caller-selected completion message, or returns null on allocation failure.
ModernPrintDialog* CreateModernPrint(PrintJob* job, const PrintSettings& settings, UINT completionMessage);

/// Opens the system print UI while retaining the source through reentrant callbacks.
HRESULT ShowModernPrint(ModernPrintDialog* source, HWND owner);

/// Closes the print source, releases its reference and reports whether printing failed.
bool CloseModernPrint(ModernPrintDialog* source);

/// Releases the source reference retained by a queued completion message.
void ReleaseModernPrint(ModernPrintDialog* source);
