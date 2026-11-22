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
 * Last modified for version 1.7.3.0
 */
#undef WINVER
#undef _WIN32_WINNT
#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#include "ModernPrintDialog.h"
#include <printmanagerinterop.h>
#include <wincodec.h>
#include <roapi.h>
#include <xmmintrin.h>

using Microsoft::WRL::ComPtr;

typedef HRESULT(WINAPI* InitializeRuntimeFunction)(RO_INIT_TYPE);
typedef void(WINAPI* UninitializeRuntimeFunction)();
typedef HRESULT(WINAPI* ActivationFactoryFunction)(HSTRING, REFIID, void**);
typedef HRESULT(WINAPI* CreateStringFunction)(PCNZWCH, UINT32, HSTRING*);
typedef HRESULT(WINAPI* DeleteStringFunction)(HSTRING);
typedef HRESULT(WINAPI* CreateD2DFactoryFunction)(D2D1_FACTORY_TYPE, REFIID,
    const D2D1_FACTORY_OPTIONS*, void**);
typedef HRESULT(WINAPI* CreateDWriteFactoryFunction)(DWRITE_FACTORY_TYPE, REFIID, IUnknown**);
typedef LONG(WINAPI* GetVersionFunction)(OSVERSIONINFOW*);

/// Maps a native printer paper identifier to the corresponding Windows print media size.
struct PrintPaperMapping {
    SHORT paper;
    Printing::PrintMediaSize size;
};

static const PrintPaperMapping printPaperSizes[] = {
    { DMPAPER_LETTER, Printing::PrintMediaSize_NorthAmericaLetter },
    { DMPAPER_LETTERSMALL, Printing::PrintMediaSize_NorthAmericaLetter },
    { DMPAPER_TABLOID, Printing::PrintMediaSize_NorthAmericaTabloid },
    { DMPAPER_LEDGER, Printing::PrintMediaSize_NorthAmericaTabloid },
    { DMPAPER_LEGAL, Printing::PrintMediaSize_NorthAmericaLegal },
    { DMPAPER_STATEMENT, Printing::PrintMediaSize_NorthAmericaStatement },
    { DMPAPER_EXECUTIVE, Printing::PrintMediaSize_NorthAmericaExecutive },
    { DMPAPER_A3, Printing::PrintMediaSize_IsoA3 },
    { DMPAPER_A4, Printing::PrintMediaSize_IsoA4 },
    { DMPAPER_A4SMALL, Printing::PrintMediaSize_IsoA4 },
    { DMPAPER_A5, Printing::PrintMediaSize_IsoA5 },
    { DMPAPER_B4, Printing::PrintMediaSize_JisB4 },
    { DMPAPER_B5, Printing::PrintMediaSize_JisB5 },
    { DMPAPER_FOLIO, Printing::PrintMediaSize_OtherMetricFolio },
    { DMPAPER_QUARTO, Printing::PrintMediaSize_NorthAmericaQuarto },
    { DMPAPER_10X14, Printing::PrintMediaSize_NorthAmerica10x14 },
    { DMPAPER_11X17, Printing::PrintMediaSize_NorthAmerica11x17 },
    { DMPAPER_NOTE, Printing::PrintMediaSize_NorthAmericaLetter },
    { DMPAPER_ENV_9, Printing::PrintMediaSize_NorthAmericaNumber9Envelope },
    { DMPAPER_ENV_10, Printing::PrintMediaSize_NorthAmericaNumber10Envelope },
    { DMPAPER_ENV_11, Printing::PrintMediaSize_NorthAmericaNumber11Envelope },
    { DMPAPER_ENV_12, Printing::PrintMediaSize_NorthAmericaNumber12Envelope },
    { DMPAPER_ENV_14, Printing::PrintMediaSize_NorthAmericaNumber14Envelope },
    { DMPAPER_CSHEET, Printing::PrintMediaSize_NorthAmericaCSheet },
    { DMPAPER_DSHEET, Printing::PrintMediaSize_NorthAmericaDSheet },
    { DMPAPER_ESHEET, Printing::PrintMediaSize_NorthAmericaESheet },
    { DMPAPER_ENV_DL, Printing::PrintMediaSize_IsoDLEnvelope },
    { DMPAPER_ENV_C5, Printing::PrintMediaSize_IsoC5Envelope },
    { DMPAPER_ENV_C3, Printing::PrintMediaSize_IsoC3Envelope },
    { DMPAPER_ENV_C4, Printing::PrintMediaSize_IsoC4Envelope },
    { DMPAPER_ENV_C6, Printing::PrintMediaSize_IsoC6Envelope },
    { DMPAPER_ENV_C65, Printing::PrintMediaSize_IsoC6C5Envelope },
    { DMPAPER_ENV_B4, Printing::PrintMediaSize_IsoB4Envelope },
    { DMPAPER_ENV_B5, Printing::PrintMediaSize_IsoB5Envelope },
    { DMPAPER_ENV_ITALY, Printing::PrintMediaSize_OtherMetricItalianEnvelope },
    { DMPAPER_ENV_MONARCH, Printing::PrintMediaSize_NorthAmericaMonarchEnvelope },
    { DMPAPER_ENV_PERSONAL, Printing::PrintMediaSize_NorthAmericaPersonalEnvelope },
    { DMPAPER_FANFOLD_STD_GERMAN, Printing::PrintMediaSize_NorthAmericaGermanStandardFanfold },
    { DMPAPER_FANFOLD_LGL_GERMAN, Printing::PrintMediaSize_NorthAmericaGermanLegalFanfold },
    { DMPAPER_ISO_B4, Printing::PrintMediaSize_IsoB4 },
    { DMPAPER_JAPANESE_POSTCARD, Printing::PrintMediaSize_JapanHagakiPostcard },
    { DMPAPER_9X11, Printing::PrintMediaSize_NorthAmerica9x11 },
    { DMPAPER_10X11, Printing::PrintMediaSize_NorthAmerica10x11 },
    { DMPAPER_LETTER_EXTRA, Printing::PrintMediaSize_NorthAmericaLetterExtra },
    { DMPAPER_LEGAL_EXTRA, Printing::PrintMediaSize_NorthAmericaLegalExtra },
    { DMPAPER_TABLOID_EXTRA, Printing::PrintMediaSize_NorthAmericaTabloidExtra },
    { DMPAPER_A4_EXTRA, Printing::PrintMediaSize_IsoA4Extra },
    { DMPAPER_LETTER_PLUS, Printing::PrintMediaSize_NorthAmericaLetterPlus },
    { DMPAPER_A4_PLUS, Printing::PrintMediaSize_OtherMetricA4Plus },
    { DMPAPER_A5_EXTRA, Printing::PrintMediaSize_IsoA5Extra },
    { DMPAPER_B5_EXTRA, Printing::PrintMediaSize_IsoB5Extra },
    { DMPAPER_A3_EXTRA, Printing::PrintMediaSize_IsoA3Extra },
    { DMPAPER_DBL_JAPANESE_POSTCARD, Printing::PrintMediaSize_JapanDoubleHagakiPostcard },
    { DMPAPER_A6, Printing::PrintMediaSize_IsoA6 },
    { DMPAPER_JENV_KAKU2, Printing::PrintMediaSize_JapanKaku2Envelope },
    { DMPAPER_JENV_KAKU3, Printing::PrintMediaSize_JapanKaku3Envelope },
    { DMPAPER_JENV_CHOU3, Printing::PrintMediaSize_JapanChou3Envelope },
    { DMPAPER_JENV_CHOU4, Printing::PrintMediaSize_JapanChou4Envelope },
    { DMPAPER_LETTER_ROTATED, Printing::PrintMediaSize_NorthAmericaLetterRotated },
    { DMPAPER_A3_ROTATED, Printing::PrintMediaSize_IsoA3Rotated },
    { DMPAPER_A4_ROTATED, Printing::PrintMediaSize_IsoA4Rotated },
    { DMPAPER_A5_ROTATED, Printing::PrintMediaSize_IsoA5Rotated },
    { DMPAPER_B4_JIS_ROTATED, Printing::PrintMediaSize_JisB4Rotated },
    { DMPAPER_B5_JIS_ROTATED, Printing::PrintMediaSize_JisB5Rotated },
    { DMPAPER_JAPANESE_POSTCARD_ROTATED, Printing::PrintMediaSize_JapanHagakiPostcardRotated },
    { DMPAPER_DBL_JAPANESE_POSTCARD_ROTATED, Printing::PrintMediaSize_JapanDoubleHagakiPostcardRotated },
    { DMPAPER_A6_ROTATED, Printing::PrintMediaSize_IsoA6Rotated },
    { DMPAPER_JENV_KAKU2_ROTATED, Printing::PrintMediaSize_JapanKaku2EnvelopeRotated },
    { DMPAPER_JENV_KAKU3_ROTATED, Printing::PrintMediaSize_JapanKaku3EnvelopeRotated },
    { DMPAPER_JENV_CHOU3_ROTATED, Printing::PrintMediaSize_JapanChou3EnvelopeRotated },
    { DMPAPER_JENV_CHOU4_ROTATED, Printing::PrintMediaSize_JapanChou4EnvelopeRotated },
    { DMPAPER_B6_JIS, Printing::PrintMediaSize_JisB6 },
    { DMPAPER_B6_JIS_ROTATED, Printing::PrintMediaSize_JisB6Rotated },
    { DMPAPER_JENV_YOU4, Printing::PrintMediaSize_JapanYou4Envelope },
    { DMPAPER_JENV_YOU4_ROTATED, Printing::PrintMediaSize_JapanYou4EnvelopeRotated },
    { DMPAPER_P16K, Printing::PrintMediaSize_Prc16K },
    { DMPAPER_P32K, Printing::PrintMediaSize_Prc32K },
    { DMPAPER_P32KBIG, Printing::PrintMediaSize_Prc32KBig },
    { DMPAPER_P16K_ROTATED, Printing::PrintMediaSize_Prc16KRotated },
    { DMPAPER_P32K_ROTATED, Printing::PrintMediaSize_Prc32KRotated },
    { DMPAPER_PENV_1, Printing::PrintMediaSize_Prc1Envelope },
    { DMPAPER_PENV_1_ROTATED, Printing::PrintMediaSize_Prc1EnvelopeRotated },
    { DMPAPER_PENV_2, Printing::PrintMediaSize_Prc2Envelope },
    { DMPAPER_PENV_2_ROTATED, Printing::PrintMediaSize_Prc2EnvelopeRotated },
    { DMPAPER_PENV_3, Printing::PrintMediaSize_Prc3Envelope },
    { DMPAPER_PENV_3_ROTATED, Printing::PrintMediaSize_Prc3EnvelopeRotated },
    { DMPAPER_PENV_4, Printing::PrintMediaSize_Prc4Envelope },
    { DMPAPER_PENV_4_ROTATED, Printing::PrintMediaSize_Prc4EnvelopeRotated },
    { DMPAPER_PENV_5, Printing::PrintMediaSize_Prc5Envelope },
    { DMPAPER_PENV_5_ROTATED, Printing::PrintMediaSize_Prc5EnvelopeRotated },
    { DMPAPER_PENV_6, Printing::PrintMediaSize_Prc6Envelope },
    { DMPAPER_PENV_6_ROTATED, Printing::PrintMediaSize_Prc6EnvelopeRotated },
    { DMPAPER_PENV_7, Printing::PrintMediaSize_Prc7Envelope },
    { DMPAPER_PENV_7_ROTATED, Printing::PrintMediaSize_Prc7EnvelopeRotated },
    { DMPAPER_PENV_8, Printing::PrintMediaSize_Prc8Envelope },
    { DMPAPER_PENV_8_ROTATED, Printing::PrintMediaSize_Prc8EnvelopeRotated },
    { DMPAPER_PENV_9, Printing::PrintMediaSize_Prc9Envelope },
    { DMPAPER_PENV_9_ROTATED, Printing::PrintMediaSize_Prc9EnvelopeRotated },
    { DMPAPER_PENV_10, Printing::PrintMediaSize_Prc10Envelope },
    { DMPAPER_PENV_10_ROTATED, Printing::PrintMediaSize_Prc10EnvelopeRotated },
};

static const CLSID imagingFactoryId = {
    0xCACAF262,
    0x9370,
    0x4615,
    { 0xA1, 0x3B, 0x9F, 0x55, 0x39, 0xDA, 0x4C, 0x0A }
};

static HMODULE runtimeModule;
static HMODULE graphicsModule;
static HMODULE drawingModule;
static HMODULE textModule;
static InitializeRuntimeFunction initializeRuntime;
static UninitializeRuntimeFunction uninitializeRuntime;
static ActivationFactoryFunction activationFactory;
static CreateStringFunction createString;
static DeleteStringFunction deleteString;
static CreateD2DFactoryFunction createFactory;
static CreateDWriteFactoryFunction createTextFactory;
static PFN_D3D11_CREATE_DEVICE createGraphics;
static bool runtimeLoaded;

extern "C" int _fltused = 0;

/// Terminates the process if a pure virtual call occurs without a C runtime handler.
extern "C" int __cdecl _purecall() {
    TerminateProcess(GetCurrentProcess(), ERROR_INVALID_FUNCTION);
    return 0;
}

/// Truncates a page coordinate to an integer without using the C runtime.
static LONG PrintCoordinate(float value) {
    return _mm_cvtt_ss2si(_mm_set_ss(value));
}

/// Loads system WinRT and graphics libraries once and resolves their optional entry points.
static HRESULT LoadPrintRuntime() {
    if (runtimeLoaded) {
        return S_OK;
    }
    if (!runtimeModule) {
        runtimeModule = LoadLibraryExW(L"combase.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    }
    if (!graphicsModule) {
        graphicsModule = LoadLibraryExW(L"d3d11.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    }
    if (!drawingModule) {
        drawingModule = LoadLibraryExW(L"d2d1.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    }
    if (!textModule) {
        textModule = LoadLibraryExW(L"dwrite.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    }
    if (!runtimeModule || !graphicsModule || !drawingModule || !textModule) {
        return HRESULT_FROM_WIN32(ERROR_MOD_NOT_FOUND);
    }
    initializeRuntime = reinterpret_cast<InitializeRuntimeFunction>(GetProcAddress(runtimeModule,
        "RoInitialize"));
    uninitializeRuntime = reinterpret_cast<UninitializeRuntimeFunction>(GetProcAddress(runtimeModule,
        "RoUninitialize"));
    activationFactory = reinterpret_cast<ActivationFactoryFunction>(GetProcAddress(runtimeModule,
        "RoGetActivationFactory"));
    createString = reinterpret_cast<CreateStringFunction>(GetProcAddress(runtimeModule,
        "WindowsCreateString"));
    deleteString = reinterpret_cast<DeleteStringFunction>(GetProcAddress(runtimeModule,
        "WindowsDeleteString"));
    createGraphics = reinterpret_cast<PFN_D3D11_CREATE_DEVICE>(GetProcAddress(graphicsModule,
        "D3D11CreateDevice"));
    createFactory = reinterpret_cast<CreateD2DFactoryFunction>(GetProcAddress(drawingModule,
        "D2D1CreateFactory"));
    createTextFactory = reinterpret_cast<CreateDWriteFactoryFunction>(GetProcAddress(textModule,
        "DWriteCreateFactory"));
    runtimeLoaded = initializeRuntime
        && uninitializeRuntime
        && activationFactory
        && createString
        && deleteString
        && createGraphics
        && createFactory
        && createTextFactory;
    return runtimeLoaded ? S_OK : HRESULT_FROM_WIN32(ERROR_PROC_NOT_FOUND);
}

/// Selects the modern printing path for Windows 11 system builds.
bool UseModernPrintDialog() {
    HMODULE module = GetModuleHandleW(L"ntdll.dll");
    if (!module) {
        return false;
    }
    GetVersionFunction getVersion =
        reinterpret_cast<GetVersionFunction>(GetProcAddress(module, "RtlGetVersion"));
    OSVERSIONINFOW version = OSVERSIONINFOW{};
    version.dwOSVersionInfoSize = sizeof(version);
    return getVersion
        && getVersion(&version) == 0
        && version.dwMajorVersion >= 10
        && version.dwBuildNumber >= 22000;
}

/// Adopts the snapshot and caller-selected completion message, or returns null on allocation failure.
ModernPrintDialog* CreateModernPrint(PrintJob* job, const PrintSettings& settings, UINT completionMessage) {
    return ModernPrintDialog::Create(job, settings, completionMessage);
}

/// Opens the system print UI while retaining the source through reentrant callbacks.
HRESULT ShowModernPrint(ModernPrintDialog* source, HWND owner) {
    source->AddRef();
    HRESULT result = source->Show(owner);
    source->Release();
    return result;
}

/// Closes the print source, releases its reference and reports whether printing failed.
bool CloseModernPrint(ModernPrintDialog* source) {
    if (!source) {
        return false;
    }
    bool failed = source->Close();
    source->Release();
    return failed;
}

/// Releases the source reference retained by a queued completion message.
void ReleaseModernPrint(ModernPrintDialog* source) {
    source->Release();
}

/// Adopts the print snapshot and copies the initial printer settings and completion message.
ModernPrintDialog::ModernPrintDialog(PrintJob* snapshot, const PrintSettings& settings,
        UINT completionMessage)
        : references(1),
        canceled(0),
        job(snapshot),
        deviceMode(DEVMODEW{}),
        pages(nullptr),
        pageCount(0),
        completeMessage(completionMessage),
        content(D2D1_RECT_F{}),
        description(Printing::PrintPageDescription{}),
        requestedToken(EventRegistrationToken{}),
        completedToken(EventRegistrationToken{}),
        requested(false),
        completed(false),
        apartment(false),
        notified(false),
        failed(false) {
    InitializeCriticalSection(&lock);
    settings.GetDeviceMode(deviceMode);
}

/// Releases the captured report, page ranges and owned graphics resources.
ModernPrintDialog::~ModernPrintDialog() {
    HeapFree(GetProcessHeap(), 0, pages);
    FreePrintJob(job);
    DeleteCriticalSection(&lock);
}

/// Uses the heap storage already allocated by Create without a C runtime allocation.
void* ModernPrintDialog::operator new(size_t, void* memory) {
    return memory;
}

/// Frees class storage from the process heap for the compiler's deleting destructors.
void ModernPrintDialog::operator delete(void* memory) {
    HeapFree(GetProcessHeap(), 0, memory);
}

/// Adopts the snapshot and caller-selected completion message, or returns null on allocation failure.
ModernPrintDialog* ModernPrintDialog::Create(PrintJob* snapshot, const PrintSettings& settings,
        UINT completionMessage) {
    void* memory = HeapAlloc(GetProcessHeap(), 0, sizeof(ModernPrintDialog));
    if (!memory) {
        FreePrintJob(snapshot);
        return nullptr;
    }
    return new(memory) ModernPrintDialog(snapshot, settings, completionMessage);
}

/// Exposes the document, preview, event callback and marshaling interfaces of this source.
HRESULT ModernPrintDialog::QueryInterface(REFIID id, void** result) {
    if (!result) {
        return E_POINTER;
    }
    *result = nullptr;
    if (id == __uuidof(IUnknown)
            || id == __uuidof(IInspectable)
            || id == __uuidof(Printing::IPrintDocumentSource)
            || id == __uuidof(IAgileObject)) {
        *result = static_cast<Printing::IPrintDocumentSource*>(this);
    } else if (id == __uuidof(IPrintDocumentPageSource)) {
        *result = static_cast<IPrintDocumentPageSource*>(this);
    } else if (id == __uuidof(IPrintPreviewPageCollection)) {
        *result = static_cast<IPrintPreviewPageCollection*>(this);
    } else if (id == __uuidof(PrintRequestedHandler)) {
        *result = static_cast<PrintRequestedHandler*>(this);
    } else if (id == __uuidof(Printing::IPrintTaskSourceRequestedHandler)) {
        *result = static_cast<Printing::IPrintTaskSourceRequestedHandler*>(this);
    } else if (id == __uuidof(PrintCompletedHandler)) {
        *result = static_cast<PrintCompletedHandler*>(this);
    } else if (id == __uuidof(PrintUiCompletedHandler)) {
        *result = static_cast<PrintUiCompletedHandler*>(this);
    } else if (id == __uuidof(IMarshal) && marshaler) {
        return marshaler->QueryInterface(id, result);
    } else {
        return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
}

/// Retains one COM reference to the print source.
ULONG ModernPrintDialog::AddRef() {
    return InterlockedIncrement(&references);
}

/// Releases one COM reference and destroys the source when no references remain.
ULONG ModernPrintDialog::Release() {
    ULONG remaining = InterlockedDecrement(&references);
    if (!remaining) {
        this->~ModernPrintDialog();
        HeapFree(GetProcessHeap(), 0, this);
    }
    return remaining;
}

/// Allocates the list of inspectable interface identifiers returned to the caller.
HRESULT ModernPrintDialog::GetIids(ULONG* count, IID** ids) {
    if (!count || !ids) {
        return E_POINTER;
    }
    *count = 0;
    *ids = static_cast<IID*>(CoTaskMemAlloc(sizeof(IID)));
    if (!*ids) {
        return E_OUTOFMEMORY;
    }
    **ids = __uuidof(Printing::IPrintDocumentSource);
    *count = 1;
    return S_OK;
}

/// Returns the Windows Runtime class name of the document source.
HRESULT ModernPrintDialog::GetRuntimeClassName(HSTRING* name) {
    if (!name) {
        return E_POINTER;
    }
    const wchar_t className[] = L"MediaInfo.PrintDocumentSource";
    return createString(className, ARRAYSIZE(className) - 1, name);
}

/// Returns the base trust level used by the document source.
HRESULT ModernPrintDialog::GetTrustLevel(TrustLevel* trust) {
    if (!trust) {
        return E_POINTER;
    }
    *trust = BaseTrust;
    return S_OK;
}

/// Registers the print callbacks and asynchronously opens the system print UI for the owner window.
HRESULT ModernPrintDialog::Show(HWND owner) {
    HRESULT result = LoadPrintRuntime();
    if (SUCCEEDED(result)) {
        result = initializeRuntime(RO_INIT_SINGLETHREADED);
        apartment = SUCCEEDED(result);
        if (result == RPC_E_CHANGED_MODE) {
            result = S_OK;
        }
    }
    if (SUCCEEDED(result)) {
        result = CoCreateFreeThreadedMarshaler(static_cast<Printing::IPrintDocumentSource*>(this),
            &marshaler);
    }
    HSTRING name = nullptr;
    ComPtr<IPrintManagerInterop> interop;
    if (SUCCEEDED(result)) {
        const wchar_t className[] = L"Windows.Graphics.Printing.PrintManager";
        result = createString(className, ARRAYSIZE(className) - 1, &name);
    }
    if (SUCCEEDED(result)) {
        result = activationFactory(name, IID_PPV_ARGS(&interop));
    }
    if (name) {
        deleteString(name);
    }
    if (SUCCEEDED(result)) {
        result = interop->GetForWindow(owner, IID_PPV_ARGS(&manager));
    }
    if (SUCCEEDED(result)) {
        result = manager->add_PrintTaskRequested(this, &requestedToken);
        requested = SUCCEEDED(result);
    }
    if (SUCCEEDED(result)) {
        result = interop->ShowPrintUIForWindowAsync(owner, IID_PPV_ARGS(&operation));
    }
    if (SUCCEEDED(result)) {
        result = operation->put_Completed(this);
    }
    if (canceled) {
        Close();
    }
    return result;
}

/// Stops pending work, removes event handlers and reports any recorded printing failure.
bool ModernPrintDialog::Close() {
    InterlockedExchange(&canceled, 1);
    EnterCriticalSection(&lock);
    job->target = nullptr;
    ComPtr<Printing::IPrintTask> oldTask = task;
    ComPtr<Printing::IPrintManager> oldManager = manager;
    ComPtr<PrintUiOperation> oldOperation = operation;
    ComPtr<IPrintDocumentPackageTarget> oldDocument = document;
    bool hadRequested = requested;
    bool hadCompleted = completed;
    requested = false;
    completed = false;
    manager.Reset();
    task.Reset();
    operation.Reset();
    preview.Reset();
    document.Reset();
    bool failure = failed;
    LeaveCriticalSection(&lock);
    if (oldDocument) {
        oldDocument->Cancel();
    }
    if (hadCompleted) {
        oldTask->remove_Completed(completedToken);
    }
    if (hadRequested) {
        oldManager->remove_PrintTaskRequested(requestedToken);
    }
    if (oldOperation) {
        ComPtr<Foundation::IAsyncInfo> info;
        if (SUCCEEDED(oldOperation.As(&info))) {
            info->Cancel();
            info->Close();
        }
    }
    oldDocument.Reset();
    oldOperation.Reset();
    oldTask.Reset();
    oldManager.Reset();
    if (apartment) {
        apartment = false;
        uninitializeRuntime();
    }
    return failure;
}

/// Records the result and posts at most one completion message with its own source reference.
void ModernPrintDialog::Complete(bool failure) {
    EnterCriticalSection(&lock);
    failed = failed || failure;
    if (!notified && job->target) {
        notified = true;
        AddRef();
        if (!PostMessageW(job->target, completeMessage, 0, reinterpret_cast<LPARAM>(this))) {
            Release();
        }
    }
    LeaveCriticalSection(&lock);
}

/// Creates the system print task and applies the captured page settings.
HRESULT ModernPrintDialog::Invoke(Printing::IPrintManager*, Printing::IPrintTaskRequestedEventArgs* args) {
    EnterCriticalSection(&lock);
    ComPtr<Printing::IPrintTaskRequest> request;
    HRESULT result = canceled ? E_ABORT : args->get_Request(&request);
    HSTRING title = nullptr;
    if (SUCCEEDED(result)) {
        result = createString(job->title, lstrlenW(job->title), &title);
    }
    if (SUCCEEDED(result)) {
        result = request->CreatePrintTask(title, this, &task);
    }
    if (title) {
        deleteString(title);
    }
    if (SUCCEEDED(result)) {
        result = task->add_Completed(this, &completedToken);
        completed = SUCCEEDED(result);
    }
    if (SUCCEEDED(result)) {
        ComPtr<Printing::IPrintTaskOptionsCore> options;
        result = task->get_Options(&options);
        if (SUCCEEDED(result)) {
            ApplySettings(options.Get());
        }
    }
    LeaveCriticalSection(&lock);
    if (FAILED(result) && !canceled) {
        Complete(true);
    }
    return result;
}

/// Supplies the captured document source when Windows requests printable content.
HRESULT ModernPrintDialog::Invoke(Printing::IPrintTaskSourceRequestedArgs* args) {
    return canceled ? E_ABORT : args->SetSource(this);
}

/// Reports the system print task result to the owning window.
HRESULT ModernPrintDialog::Invoke(Printing::IPrintTask*, Printing::IPrintTaskCompletedEventArgs* args) {
    Printing::PrintTaskCompletion completion;
    HRESULT result = args->get_Completion(&completion);
    Complete(FAILED(result) || completion == Printing::PrintTaskCompletion_Failed);
    return result;
}

/// Completes the request if showing the system print UI fails or is canceled.
HRESULT ModernPrintDialog::Invoke(PrintUiOperation* sender, Foundation::AsyncStatus status) {
    boolean shown = false;
    HRESULT result = status == Foundation::AsyncStatus::Completed ? sender->GetResults(&shown) : E_ABORT;
    if (FAILED(result) || !shown) {
        Complete(status == Foundation::AsyncStatus::Error);
    }
    return S_OK;
}

/// Creates the software graphics device, Direct2D context and DirectWrite text resources.
HRESULT ModernPrintDialog::InitializeGraphics() {
    if (context && ink && textFormat) {
        return S_OK;
    }
    D2D1_FACTORY_OPTIONS options = D2D1_FACTORY_OPTIONS{};
    HRESULT result = createFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, __uuidof(ID2D1Factory1), &options,
        reinterpret_cast<void**>(factory.ReleaseAndGetAddressOf()));
    if (SUCCEEDED(result)) {
        result = createGraphics(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
            nullptr, 0, D3D11_SDK_VERSION, graphics.ReleaseAndGetAddressOf(), nullptr, nullptr);
    }
    ComPtr<IDXGIDevice> dxgi;
    if (SUCCEEDED(result)) {
        result = graphics.As(&dxgi);
    }
    if (SUCCEEDED(result)) {
        result = factory->CreateDevice(dxgi.Get(), device.ReleaseAndGetAddressOf());
    }
    if (SUCCEEDED(result)) {
        result = device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
            context.ReleaseAndGetAddressOf());
    }
    if (SUCCEEDED(result)) {
        result = context->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black),
            ink.ReleaseAndGetAddressOf());
    }
    if (SUCCEEDED(result)) {
        result = createTextFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
            reinterpret_cast<IUnknown**>(textFactory.ReleaseAndGetAddressOf()));
    }
    if (SUCCEEDED(result)) {
        result = InitializeTextFormat();
    }
    return result;
}

/// Matches the captured edit font and retains its size in device-independent units.
HRESULT ModernPrintDialog::InitializeTextFormat() {
    if (!job->fontDpi) {
        return E_INVALIDARG;
    }
    ComPtr<IDWriteGdiInterop> interop;
    HRESULT result = textFactory->GetGdiInterop(&interop);
    ComPtr<IDWriteFont> font;
    if (SUCCEEDED(result)) {
        result = interop->CreateFontFromLOGFONT(&job->font, &font);
    }
    ComPtr<IDWriteFontFamily> family;
    if (SUCCEEDED(result)) {
        result = font->GetFontFamily(&family);
    }
    ComPtr<IDWriteLocalizedStrings> names;
    if (SUCCEEDED(result)) {
        result = family->GetFamilyNames(&names);
    }
    UINT32 length = 0;
    if (SUCCEEDED(result)) {
        result = names->GetStringLength(0, &length);
    }
    wchar_t* name = nullptr;
    if (SUCCEEDED(result)) {
        if (length >= MAXDWORD / sizeof(wchar_t)) {
            return E_OUTOFMEMORY;
        }
        name = static_cast<wchar_t*>(HeapAlloc(GetProcessHeap(), 0, (length + 1) * sizeof(wchar_t)));
        result = name ? names->GetString(0, name, length + 1) : E_OUTOFMEMORY;
    }
    if (SUCCEEDED(result)) {
        DWRITE_FONT_METRICS metrics;
        font->GetMetrics(&metrics);
        float size = static_cast<float>(job->font.lfHeight) * 96.0f / job->fontDpi;
        if (size < 0) {
            size = -size;
        } else if (size > 0) {
            size *= static_cast<float>(metrics.designUnitsPerEm) / (metrics.ascent + metrics.descent);
        } else {
            size = 12.0f;
        }
        wchar_t locale[LOCALE_NAME_MAX_LENGTH] = L"";
        GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SNAME, locale, ARRAYSIZE(locale));
        result = textFactory->CreateTextFormat(name, nullptr, font->GetWeight(), font->GetStyle(),
            font->GetStretch(), size, locale, textFormat.ReleaseAndGetAddressOf());
        ComPtr<IDWriteFontFace> face;
        if (SUCCEEDED(result)) {
            result = font->CreateFontFace(&face);
        }
        UINT32 space = L' ';
        UINT16 glyph = 0;
        DWRITE_GLYPH_METRICS advance = DWRITE_GLYPH_METRICS{};
        if (SUCCEEDED(result)) {
            result = face->GetGlyphIndices(&space, 1, &glyph);
        }
        if (SUCCEEDED(result)) {
            result = face->GetDesignGlyphMetrics(&glyph, 1, &advance);
        }
        if (SUCCEEDED(result)) {
            result = textFormat->SetIncrementalTabStop(8.0f * advance.advanceWidth * size
                / metrics.designUnitsPerEm);
        }
    }
    HeapFree(GetProcessHeap(), 0, name);
    if (FAILED(result)) {
        textFormat.Reset();
    }
    return result;
}

/// Groups complete DirectWrite lines into pages within the current printable area.
HRESULT ModernPrintDialog::BuildPages() {
    HeapFree(GetProcessHeap(), 0, pages);
    pages = nullptr;
    pageCount = 0;
    float width = content.right - content.left;
    float height = content.bottom - content.top;
    if (width <= 0 || height <= 0) {
        return E_INVALIDARG;
    }
    ComPtr<IDWriteTextLayout> layout;
    HRESULT result = textFactory->CreateTextLayout(job->report, lstrlenW(job->report), textFormat.Get(),
        width, height, &layout);
    if (SUCCEEDED(result) && job->formatLayout) {
        result = job->formatLayout(job, layout.Get(), context.Get(), 0, lstrlenW(job->report));
    }
    UINT32 count = 0;
    if (SUCCEEDED(result)) {
        result = layout->GetLineMetrics(nullptr, 0, &count);
        if (result == HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER)) {
            result = S_OK;
        }
    }
    DWRITE_LINE_METRICS* lines = nullptr;
    if (SUCCEEDED(result)) {
        if (!count || count > MAXDWORD / sizeof(DWRITE_LINE_METRICS)) {
            return E_OUTOFMEMORY;
        }
        lines = static_cast<DWRITE_LINE_METRICS*>(HeapAlloc(GetProcessHeap(), 0,
            count * sizeof(DWRITE_LINE_METRICS)));
        pages = static_cast<ModernPrintPage*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
            count * sizeof(ModernPrintPage)));
        result = lines && pages ? layout->GetLineMetrics(lines, count, &count) : E_OUTOFMEMORY;
    }
    if (SUCCEEDED(result)) {
        pageCount = 1;
        float used = 0;
        UINT32 position = 0;
        for (UINT32 index = 0; index < count; ++index) {
            const DWRITE_LINE_METRICS& line = lines[index];
            if (!line.length && index) {
                break;
            }
            if (line.height > height) {
                result = E_INVALIDARG;
                pageCount = 0;
                break;
            }
            if (used > 0 && used + line.height > height) {
                pages[pageCount++].start = position;
                used = 0;
            }
            pages[pageCount - 1].length += line.length;
            position += line.length;
            used += line.height;
        }
    }
    HeapFree(GetProcessHeap(), 0, lines);
    return result;
}

/// Rebuilds pagination from the selected paper size, printable area, margins and edit font.
HRESULT ModernPrintDialog::Prepare(IInspectable* options) {
    HRESULT result = InitializeGraphics();
    ComPtr<Printing::IPrintTaskOptionsCore> core;
    if (SUCCEEDED(result)) {
        result = options->QueryInterface(IID_PPV_ARGS(&core));
    }
    if (SUCCEEDED(result)) {
        result = core->GetPageDescription(0, &description);
    }
    if (SUCCEEDED(result)) {
        const Foundation::Rect& image = description.ImageableRect;
        D2D1_RECT_F margins = D2D1::RectF(
            job->margins.left * 96.0f / 2540.0f,
            job->margins.top * 96.0f / 2540.0f,
            description.PageSize.Width - job->margins.right * 96.0f / 2540.0f,
            description.PageSize.Height - job->margins.bottom * 96.0f / 2540.0f);
        content = D2D1::RectF(image.X, image.Y, image.X + image.Width, image.Y + image.Height);
        if (content.left < margins.left) {
            content.left = margins.left;
        }
        if (content.top < margins.top) {
            content.top = margins.top;
        }
        if (content.right > margins.right) {
            content.right = margins.right;
        }
        if (content.bottom > margins.bottom) {
            content.bottom = margins.bottom;
        }
        result = BuildPages();
    }
    return result;
}

/// Connects the system preview target and returns this source's preview page collection.
HRESULT ModernPrintDialog::GetPreviewPageCollection(IPrintDocumentPackageTarget* target,
        IPrintPreviewPageCollection** collection) {
    if (!collection) {
        return E_POINTER;
    }
    *collection = nullptr;
    EnterCriticalSection(&lock);
    HRESULT result = canceled
        ? E_ABORT
        : target->GetPackageTarget(ID_PREVIEWPACKAGETARGET_DXGI, IID_PPV_ARGS(&preview));
    if (SUCCEEDED(result)) {
        *collection = static_cast<IPrintPreviewPageCollection*>(this);
        AddRef();
    }
    LeaveCriticalSection(&lock);
    return result;
}

/// Recalculates the layout for changed print options and publishes the final page count.
HRESULT ModernPrintDialog::Paginate(UINT32, IInspectable* options) {
    EnterCriticalSection(&lock);
    HRESULT result = canceled ? E_ABORT : Prepare(options);
    if (SUCCEEDED(result) && preview) {
        result = preview->SetJobPageCount(FinalPageCount, pageCount);
    }
    LeaveCriticalSection(&lock);
    return result;
}

/// Records one zero-based document page as text glyphs in a Direct2D command list.
HRESULT ModernPrintDialog::CreatePage(UINT page, ID2D1CommandList** result) {
    *result = nullptr;
    if (page >= pageCount) {
        return E_INVALIDARG;
    }
    const ModernPrintPage& range = pages[page];
    ComPtr<IDWriteTextLayout> layout;
    HRESULT status = textFactory->CreateTextLayout(job->report + range.start, range.length, textFormat.Get(),
        content.right - content.left, content.bottom - content.top, &layout);
    DWRITE_TEXT_RANGE text = DWRITE_TEXT_RANGE{ 0, range.length };
    if (SUCCEEDED(status) && job->font.lfUnderline) {
        status = layout->SetUnderline(TRUE, text);
    }
    if (SUCCEEDED(status) && job->font.lfStrikeOut) {
        status = layout->SetStrikethrough(TRUE, text);
    }
    if (SUCCEEDED(status) && job->formatLayout) {
        status = job->formatLayout(job, layout.Get(), context.Get(), range.start, range.length);
    }
    ComPtr<ID2D1CommandList> commands;
    if (SUCCEEDED(status)) {
        status = context->CreateCommandList(&commands);
    }
    if (SUCCEEDED(status)) {
        context->SetTarget(commands.Get());
        context->SetDpi(96, 96);
        context->SetTransform(D2D1::Matrix3x2F::Identity());
        context->SetTextAntialiasMode(job->font.lfQuality == NONANTIALIASED_QUALITY
            ? D2D1_TEXT_ANTIALIAS_MODE_ALIASED
            : D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
        context->BeginDraw();
        context->Clear(D2D1::ColorF(D2D1::ColorF::White));
        context->PushAxisAlignedClip(content, D2D1_ANTIALIAS_MODE_ALIASED);
        context->DrawTextLayout(D2D1::Point2F(content.left, content.top), layout.Get(), ink.Get(),
            D2D1_DRAW_TEXT_OPTIONS_NO_SNAP);
        context->PopAxisAlignedClip();
        status = context->EndDraw();
        context->SetTarget(nullptr);
    }
    if (SUCCEEDED(status)) {
        status = commands->Close();
    }
    if (SUCCEEDED(status)) {
        *result = commands.Detach();
    }
    return status;
}

/// Renders the requested one-based page to a DXGI surface for the system preview.
HRESULT ModernPrintDialog::MakePage(UINT32 page, FLOAT width, FLOAT height) {
    EnterCriticalSection(&lock);
    if (page == JOB_PAGE_APPLICATION_DEFINED) {
        page = 1;
    }
    ComPtr<ID2D1CommandList> commands;
    HRESULT result = canceled ? E_ABORT : page ? CreatePage(page - 1, &commands) : E_INVALIDARG;
    ComPtr<ID3D11Texture2D> texture;
    D3D11_TEXTURE2D_DESC textureDescription = D3D11_TEXTURE2D_DESC{};
    textureDescription.Width = PrintCoordinate(width + 0.5f);
    textureDescription.Height = PrintCoordinate(height + 0.5f);
    textureDescription.MipLevels = 1;
    textureDescription.ArraySize = 1;
    textureDescription.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    textureDescription.SampleDesc.Count = 1;
    textureDescription.Usage = D3D11_USAGE_DEFAULT;
    textureDescription.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    if (SUCCEEDED(result)) {
        result = graphics->CreateTexture2D(&textureDescription, nullptr, &texture);
    }
    ComPtr<IDXGISurface> surface;
    if (SUCCEEDED(result)) {
        result = texture.As(&surface);
    }
    ComPtr<ID2D1Bitmap1> bitmap;
    D2D1_BITMAP_PROPERTIES1 properties = D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE));
    if (SUCCEEDED(result)) {
        result = context->CreateBitmapFromDxgiSurface(surface.Get(), &properties, &bitmap);
    }
    float dpiX = width * 96.0f / description.PageSize.Width;
    float dpiY = height * 96.0f / description.PageSize.Height;
    if (SUCCEEDED(result)) {
        context->SetTarget(bitmap.Get());
        context->SetDpi(dpiX, dpiY);
        context->BeginDraw();
        context->Clear(D2D1::ColorF(D2D1::ColorF::White));
        context->DrawImage(commands.Get());
        result = context->EndDraw();
        context->SetTarget(nullptr);
    }
    if (SUCCEEDED(result)) {
        result = preview ? preview->DrawPage(page, surface.Get(), dpiX, dpiY) : E_UNEXPECTED;
    }
    LeaveCriticalSection(&lock);
    return result;
}

/// Writes all final pages to the system package target and cancels the package on failure.
HRESULT ModernPrintDialog::MakeDocument(IInspectable* options, IPrintDocumentPackageTarget* target) {
    EnterCriticalSection(&lock);
    document = target;
    HRESULT result = canceled ? E_ABORT : Prepare(options);
    ComPtr<IWICImagingFactory> imaging;
    if (SUCCEEDED(result)) {
        result = CoCreateInstance(imagingFactoryId, nullptr, CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&imaging));
    }
    ComPtr<ID2D1PrintControl> printing;
    if (SUCCEEDED(result)) {
        D2D1_PRINT_CONTROL_PROPERTIES properties =
            D2D1::PrintControlProperties(D2D1_PRINT_FONT_SUBSET_MODE_DEFAULT, 300.0f, D2D1_COLOR_SPACE_SRGB);
        result = device->CreatePrintControl(imaging.Get(), target, &properties, &printing);
    }
    for (UINT page = 0; SUCCEEDED(result) && page < pageCount; ++page) {
        ComPtr<ID2D1CommandList> commands;
        result = canceled ? E_ABORT : CreatePage(page, &commands);
        if (SUCCEEDED(result)) {
            D2D_SIZE_F size = D2D1::SizeF(description.PageSize.Width, description.PageSize.Height);
            result = printing->AddPage(commands.Get(), size, nullptr);
        }
    }
    if (SUCCEEDED(result)) {
        result = printing->Close();
    }
    if (FAILED(result)) {
        target->Cancel();
    }
    document.Reset();
    LeaveCriticalSection(&lock);
    if (FAILED(result) && !canceled) {
        Complete(true);
    }
    return result;
}

/// Applies the stored paper size and orientation to the system print task options.
void ModernPrintDialog::ApplySettings(Printing::IPrintTaskOptionsCore* options) const {
    ComPtr<Printing::IPrintTaskOptionsCoreProperties> properties;
    if (FAILED(options->QueryInterface(IID_PPV_ARGS(&properties)))) {
        return;
    }
    if (deviceMode.dmFields & DM_ORIENTATION) {
        bool landscape = deviceMode.dmOrientation == DMORIENT_LANDSCAPE;
        if (deviceMode.dmFields & DM_PAPERSIZE && deviceMode.dmPaperSize == DMPAPER_LEDGER) {
            landscape = !landscape;
        }
        properties->put_Orientation(landscape
            ? Printing::PrintOrientation_Landscape
            : Printing::PrintOrientation_Portrait);
    }
    if (deviceMode.dmFields & DM_PAPERSIZE) {
        for (UINT index = 0; index < ARRAYSIZE(printPaperSizes); ++index) {
            if (printPaperSizes[index].paper == deviceMode.dmPaperSize) {
                properties->put_MediaSize(printPaperSizes[index].size);
                break;
            }
        }
    }
}
