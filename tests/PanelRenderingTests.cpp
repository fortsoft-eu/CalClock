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
 * Last modified for version 1.6.0.0
 */

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>

/// Records native panel creation without changing its class, styles, or parent.
static HWND WINAPI RecordPanelWindow(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);

/// Observes the application's real window-position batch without altering it.
static BOOL WINAPI PresentRecordedPanel(HDWP);

#define CreateWindowExW RecordPanelWindow
#define EndDeferWindowPos PresentRecordedPanel
#define main ExistingSettingsLayoutTestMain
#include "SettingsLayoutTests.cpp"
#undef main
#undef EndDeferWindowPos
#undef CreateWindowExW
#include <d3d11.h>
#include <dxgi1_2.h>
#include <windows.graphics.capture.interop.h>
#include <windows.graphics.directx.direct3d11.interop.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Graphics.Capture.h>
#include <winrt/Windows.Graphics.DirectX.h>
#include <winrt/Windows.Graphics.DirectX.Direct3D11.h>
#include <mutex>
#include <thread>

using winrt::Windows::Graphics::Capture::Direct3D11CaptureFramePool;
using winrt::Windows::Graphics::Capture::GraphicsCaptureItem;
using winrt::Windows::Graphics::DirectX::DirectXPixelFormat;
using winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice;


static HWND sceneWindow = nullptr;
static HWND captureCover = nullptr;
static HWND captureWindow = nullptr;
static Direct3D11CaptureFramePool scenePool{ nullptr };
static winrt::Windows::Graphics::Capture::GraphicsCaptureSession sceneSession{ nullptr };
static winrt::event_token sceneToken = {};
static winrt::com_ptr<ID3D11Device> captureDevice;
static winrt::com_ptr<ID3D11DeviceContext> captureContext;
static Widget* panelUnderTest = nullptr;
static Widget* preparedPanel = nullptr;
static RECT captureCoveredBounds = {};
static HRESULT captureFailure = S_OK;
static std::mutex captureLock;
static bool observePanelSwaps = false;
static bool negativeSceneGap = false;
static int capturedVariant = 0;
static int preparedSwaps = 0;
static int comparedFrames = 0;
static int mismatchedFrames = 0;
static std::vector<FieldImage> capturedFrames;

/// Records only native panel windows created by the application under test.
static HWND WINAPI RecordPanelWindow(DWORD extended, LPCWSTR name, LPCWSTR text, DWORD style,
        int x, int y, int width, int height, HWND parent, HMENU menu, HINSTANCE instance, LPVOID parameter) {
    HWND window = CreateWindowExW(extended, name, text, style, x, y, width, height, parent, menu, instance, parameter);
    if (observePanelSwaps
            && name == CLASS_NAME
            && parameter != nullptr
            && static_cast<Widget*>(parameter)->config.type == WIDGET_PANEL) {
        preparedPanel = static_cast<Widget*>(parameter);
    }
    return window;
}

/// Pumps a bounded number of messages so a paint loop cannot prevent its own detection.
static void PumpPanelMessages() {
    MSG message = {};
    for (int count = 0; count < 256 && PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE); count++) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }
    GdiFlush();
}

/// Allows only test-owned secondary windows to enter the composite capture.
static bool PanelSceneIsPrivate() {
    if (sceneWindow == nullptr || !IsWindow(sceneWindow)) {
        return false;
    }
    RECT sceneBounds = {};
    GetWindowRect(sceneWindow, &sceneBounds);
    for (HWND sibling = GetWindow(sceneWindow, GW_HWNDPREV);
            sibling != nullptr;
            sibling = GetWindow(sibling, GW_HWNDPREV)) {
        RECT siblingBounds = {};
        RECT intersection = {};
        GetWindowRect(sibling, &siblingBounds);
        if (!IsWindowVisible(sibling) || !IntersectRect(&intersection, &sceneBounds, &siblingBounds)) {
            continue;
        }
        LONG_PTR style = GetWindowLongPtrW(sibling, GWL_STYLE);
        LONG_PTR extended = GetWindowLongPtrW(sibling, GWL_EXSTYLE);
        if ((style & WS_POPUP) == 0 && (extended & WS_EX_TOOLWINDOW) == 0) {
            break;
        }
        DWORD process = 0;
        GetWindowThreadProcessId(sibling, &process);
        if (process != GetCurrentProcessId()) {
            return false;
        }
    }
    return true;
}

/// Reads compositor frames without acquiring or releasing any DC belonging to the widget.
static void CapturePanelFrame(const Direct3D11CaptureFramePool& pool) {
    try {
        if (!PanelSceneIsPrivate()) {
            std::lock_guard<std::mutex> lock(captureLock);
            captureFailure = E_ABORT;
            return;
        }
        auto frame = pool.TryGetNextFrame();
        if (!frame) {
            return;
        }
        auto access = frame.Surface().as<Windows::Graphics::DirectX::Direct3D11::IDirect3DDxgiInterfaceAccess>();
        winrt::com_ptr<ID3D11Texture2D> texture;
        winrt::check_hresult(access->GetInterface(__uuidof(ID3D11Texture2D), texture.put_void()));
        D3D11_TEXTURE2D_DESC description = {};
        texture->GetDesc(&description);
        description.Usage = D3D11_USAGE_STAGING;
        description.BindFlags = 0;
        description.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        description.MiscFlags = 0;
        winrt::com_ptr<ID3D11Texture2D> staging;
        winrt::check_hresult(captureDevice->CreateTexture2D(&description, nullptr, staging.put()));
        captureContext->CopyResource(staging.get(), texture.get());
        D3D11_MAPPED_SUBRESOURCE mapped = {};
        winrt::check_hresult(captureContext->Map(staging.get(), 0, D3D11_MAP_READ, 0, &mapped));
        FieldImage image = { static_cast<int>(description.Width), static_cast<int>(description.Height), {} };
        image.pixels.resize(static_cast<size_t>(image.width) * image.height);
        for (int y = 0; y < image.height; y++) {
            memcpy(image.pixels.data() + static_cast<size_t>(y) * image.width, static_cast<BYTE*>(mapped.pData)
                + static_cast<size_t>(y) * mapped.RowPitch, static_cast<size_t>(image.width) * sizeof(DWORD));
        }
        captureContext->Unmap(staging.get(), 0);
        frame.Close();
        std::lock_guard<std::mutex> lock(captureLock);
        capturedFrames.push_back(std::move(image));
    } catch (const winrt::hresult_error& error) {
        std::lock_guard<std::mutex> lock(captureLock);
        captureFailure = error.code();
    }
}

/// Collects monitor work areas for positioning the fully covered test window.
static BOOL CALLBACK CaptureMonitorArea(HMONITOR monitor, HDC, LPRECT, LPARAM data) {
    MONITORINFO information = { sizeof(information) };
    if (GetMonitorInfoW(monitor, &information)) {
        reinterpret_cast<std::vector<RECT>*>(data)->push_back(information.rcWork);
    }
    return TRUE;
}

/// Checks that an opaque window covers every sampled point without requiring it to remain the same application.
static bool IsCaptureAreaCovered(HWND cover, const RECT& bounds) {
    for (int y = bounds.top; y < bounds.bottom; y += 10) {
        for (int x = bounds.left; x < bounds.right; x += 10) {
            HWND top = GetAncestor(WindowFromPoint(POINT{ x, y }), GA_ROOT);
            DWORD process = 0;
            GetWindowThreadProcessId(top, &process);
            if (process == GetCurrentProcessId()) {
                return false;
            }
            if (top != cover) {
                wchar_t className[128] = {};
                GetClassNameW(top, className, ARRAYSIZE(className));
                if (captureWindow == nullptr
                        || top == nullptr
                        || top == captureWindow
                        || wcscmp(className, L"Progman") == 0
                        || wcscmp(className, L"WorkerW") == 0
                        || (GetWindowLongPtrW(top, GWL_EXSTYLE) & (WS_EX_LAYERED | WS_EX_TRANSPARENT)) != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

/// Finds an opaque covering window without activating, moving, or capturing another application.
static bool FindCoveredCaptureArea(SIZE size, RECT* result) {
    std::vector<RECT> areas;
    EnumDisplayMonitors(nullptr, nullptr, CaptureMonitorArea, reinterpret_cast<LPARAM>(&areas));
    const POINT offsets[] = {
        POINT{ 64, 64 },
        POINT{ 400, 200 },
        POINT{ 200, 400 },
        POINT{ 700, 100 }
    };
    for (const RECT& work : areas) {
        for (POINT offset : offsets) {
            if (work.left + offset.x < 0 || work.top + offset.y < 0) {
                continue;
            }
            RECT candidate = {
                work.left + offset.x,
                work.top + offset.y,
                work.left + offset.x + size.cx,
                work.top + offset.y + size.cy
            };
            if (candidate.right > work.right || candidate.bottom > work.bottom) {
                continue;
            }
            POINT center = { (candidate.left + candidate.right) / 2, (candidate.top + candidate.bottom) / 2 };
            HWND cover = GetAncestor(WindowFromPoint(center), GA_ROOT);
            wchar_t name[64] = {};
            GetClassNameW(cover, name, ARRAYSIZE(name));
            if (cover == nullptr
                    || (GetWindowLongPtrW(cover, GWL_STYLE) & WS_POPUP) != 0
                    || (GetWindowLongPtrW(cover, GWL_EXSTYLE) & WS_EX_TOOLWINDOW) != 0
                    || wcscmp(name, L"Progman") == 0
                    || wcscmp(name, L"WorkerW") == 0
                    || (GetWindowLongPtrW(cover, GWL_EXSTYLE) & (WS_EX_LAYERED | WS_EX_TRANSPARENT)) != 0) {
                continue;
            }
            if (IsCaptureAreaCovered(cover, candidate)) {
                captureCover = cover;
                captureCoveredBounds = candidate;
                *result = candidate;
                return true;
            }
        }
    }
    return false;
}

/// Hides the test-owned widget and aborts if the covering window moves away.
static void CheckCaptureAreaCovered() {
    if (!IsCaptureAreaCovered(captureCover, captureCoveredBounds)) {
        ShowWindow(captureWindow, SW_HIDE);
        ShowWindow(sceneWindow, SW_HIDE);
        if (panelUnderTest != nullptr) {
            ShowWindow(panelUnderTest->window, SW_HIDE);
        }
        throw winrt::hresult_error(E_ABORT, L"The covering window moved; test window was hidden.");
    }
}

/// Pumps the native test window while allowing the compositor and capture worker to complete their frames.
static void PumpCaptureFor(DWORD milliseconds) {
    ULONGLONG deadline = GetTickCount64() + milliseconds;
    while (GetTickCount64() < deadline) {
        PumpPanelMessages();
        CheckCaptureAreaCovered();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

/// Confirms that a reference contains actual native calendar, clock, or link pixels at its expected control rectangle.
static bool ReferenceContainsControl(const FieldImage& image, const RECT& bounds, size_t control) {
    int count = 0;
    for (int y = std::max(0L, bounds.top); y < std::min<LONG>(image.height, bounds.bottom); y++) {
        for (int x = std::max(0L, bounds.left); x < std::min<LONG>(image.width, bounds.right); x++) {
            DWORD pixel = image.pixels[static_cast<size_t>(y) * image.width + x];
            int red = pixel >> 16 & 0xFF;
            int green = pixel >> 8 & 0xFF;
            int blue = pixel & 0xFF;
            bool ink = false;
            if (control == 0) {
                ink = red < 150 && green < 150 && blue < 150;
            } else if (control == 1 || control >= 4) {
                ink = red >= 50 && red < 240 && green > red + 2 && blue >= green;
            } else {
                ink = blue > red + 40 && blue > green + 20;
            }
            if (ink) {
                count++;
            }
        }
    }
    return count >= (control == 2 || control == 3 ? 20 : 100);
}

/// Verifies complete native calendar, clocks, and links on a real window surface.
static void CheckPanelSurface(Widget* widget, const FieldImage& image) {
    RECT root = {};
    GetWindowRect(widget->window, &root);
    const HWND controls[] = {
        widget->calendarChild,
        widget->analogChild,
        widget->panelDateLink,
        widget->panelTimeZoneLink,
        widget->additionalAnalogChildren[0],
        widget->additionalAnalogChildren[1]
    };
    for (size_t index = 0; index < ARRAYSIZE(controls); index++) {
        if (controls[index] != nullptr) {
            RECT bounds = {};
            GetWindowRect(controls[index], &bounds);
            OffsetRect(&bounds, -root.left, -root.top);
            Check(ReferenceContainsControl(image, bounds, index), "the complete native control is already rendered");
        }
    }
}

/// Compares every pixel, including clock hands, native frame edges, links, and all client margins.
static bool SameCompletePanelSurface(const FieldImage& left, const FieldImage& right, bool compareAlpha = false) {
    if (left.width != right.width || left.height != right.height) {
        return false;
    }
    DWORD mask = compareAlpha ? 0xFFFFFFFF : 0xFFFFFF;
    for (size_t pixel = 0; pixel < left.pixels.size(); pixel++) {
        if ((left.pixels[pixel] & mask) != (right.pixels[pixel] & mask)) {
            return false;
        }
    }
    return true;
}

/// Exposes the interval between native background erasure and content painting under temporary rendering delays.
static LRESULT CALLBACK DelayNativeControlErase(HWND window, UINT message, WPARAM wParam, LPARAM lParam,
        UINT_PTR, DWORD_PTR) {
    LRESULT result = DefSubclassProc(window, message, wParam, lParam);
    if (message == WM_ERASEBKGND) {
        Sleep(35);
    }
    return result;
}

/// Paints only the test's opaque checkerboard so a missing panel reveals a recognizable background.
static LRESULT CALLBACK SceneWindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_ERASEBKGND) {
        return 1;
    }
    if (message == WM_PAINT) {
        PAINTSTRUCT paint = {};
        HDC dc = BeginPaint(window, &paint);
        RECT client = {};
        GetClientRect(window, &client);
        HBRUSH brushes[] = { CreateSolidBrush(RGB(211, 37, 183)), CreateSolidBrush(RGB(29, 201, 147)) };
        for (LONG y = 0; y < client.bottom; y += 16) {
            for (LONG x = 0; x < client.right; x += 16) {
                RECT cell = { x, y, std::min(client.right, x + 16), std::min(client.bottom, y + 16) };
                FillRect(dc, &cell, brushes[(x / 16 + y / 16) % 2]);
            }
        }
        DeleteObject(brushes[0]);
        DeleteObject(brushes[1]);
        EndPaint(window, &paint);
        return 0;
    }
    return DefWindowProcW(window, message, wParam, lParam);
}

/// Captures the checkerboard and all test-owned native panel windows in their real top-level z-order.
static void StartSceneCapture() {
    auto dxgi = captureDevice.as<IDXGIDevice>();
    winrt::com_ptr<IInspectable> inspectable;
    winrt::check_hresult(CreateDirect3D11DeviceFromDXGIDevice(dxgi.get(), inspectable.put()));
    auto device = inspectable.as<IDirect3DDevice>();
    auto factory = winrt::get_activation_factory<GraphicsCaptureItem, IGraphicsCaptureItemInterop>();
    GraphicsCaptureItem item = nullptr;
    winrt::check_hresult(factory->CreateForWindow(sceneWindow, winrt::guid_of<GraphicsCaptureItem>(),
        winrt::put_abi(item)));
    scenePool = Direct3D11CaptureFramePool::CreateFreeThreaded(device, DirectXPixelFormat::B8G8R8A8UIntNormalized,
        3, item.Size());
    sceneToken = scenePool.FrameArrived([](const auto& sender, const auto&) { CapturePanelFrame(sender); });
    if (!PanelSceneIsPrivate()) {
        throw winrt::hresult_error(E_ABORT, L"A foreign secondary window would enter the test scene capture.");
    }
    sceneSession = scenePool.CreateCaptureSession(item);
    sceneSession.IsCursorCaptureEnabled(false);
    sceneSession.IncludeSecondaryWindows(true);
    sceneSession.StartCapture();
    PumpCaptureFor(160);
}

/// Rejects revealed background and partial presentation by checking the final scene against the native opaque surface.
static bool SceneContainsPanel(const Widget* widget, const FieldImage& scene, const FieldImage& native) {
    RECT stage = {};
    RECT root = {};
    RECT client = {};
    GetWindowRect(sceneWindow, &stage);
    GetWindowRect(widget->window, &root);
    GetClientRect(widget->window, &client);
    MapWindowPoints(widget->window, HWND_DESKTOP, reinterpret_cast<POINT*>(&client), 2);
    int alpha = widget->config.opacity * 255 / 100;
    for (LONG y = client.top; y < client.bottom; y++) {
        for (LONG x = client.left; x < client.right; x++) {
            size_t panelPixel = static_cast<size_t>(y - root.top) * native.width + x - root.left;
            size_t scenePixel = static_cast<size_t>(y - stage.top) * scene.width + x - stage.left;
            COLORREF color = ((x - stage.left) / 16 + (y - stage.top) / 16) % 2 == 0
                ? RGB(211, 37, 183)
                : RGB(29, 201, 147);
            DWORD background = GetRValue(color) << 16 | GetGValue(color) << 8 | GetBValue(color);
            for (int shift = 0; shift < 24; shift += 8) {
                int foregroundChannel = native.pixels[panelPixel] >> shift & 0xFF;
                int backgroundChannel = background >> shift & 0xFF;
                int expected = (foregroundChannel * alpha + backgroundChannel * (255 - alpha) + 127) / 255;
                int actual = scene.pixels[scenePixel] >> shift & 0xFF;
                if (abs(expected - actual) > 3) {
                    return false;
                }
            }
        }
    }
    return true;
}

/// Compares the complete scene exactly, allowing only native calendar text rasterization rounding during erasure.
static bool SamePanelScene(const FieldImage& actual, const FieldImage& reference, const RECT& calendar) {
    if (actual.width != reference.width
            || actual.height != reference.height
            || actual.pixels.size() != reference.pixels.size()) {
        return false;
    }
    for (int y = 0; y < actual.height; y++) {
        for (int x = 0; x < actual.width; x++) {
            size_t pixel = static_cast<size_t>(y) * actual.width + x;
            if (actual.pixels[pixel] == reference.pixels[pixel]) {
                continue;
            }
            if (x < calendar.left
                    || x >= calendar.right
                    || y < calendar.top
                    || y >= calendar.bottom
                    || actual.pixels[pixel] >> 24 != reference.pixels[pixel] >> 24) {
                return false;
            }
            for (int shift = 0; shift < 24; shift += 8) {
                int left = actual.pixels[pixel] >> shift & 0xFF;
                int right = reference.pixels[pixel] >> shift & 0xFF;
                if (abs(left - right) > 2) {
                    return false;
                }
            }
        }
    }
    return true;
}

/// Returns the calendar's actual coordinates in the captured composite scene.
static RECT SceneCalendarBounds(const Widget* widget) {
    RECT stage = {};
    RECT calendar = {};
    GetWindowRect(sceneWindow, &stage);
    GetWindowRect(widget->calendarChild, &calendar);
    OffsetRect(&calendar, -stage.left, -stage.top);
    return calendar;
}

/// Copies the latest captured scene and clears the capture queue under one lock.
/// Returns false when no previous scene is available.
static bool TakePreviousPanelScene(FieldImage& scene) {
    std::lock_guard<std::mutex> lock(captureLock);
    Check(!capturedFrames.empty(), "previous complete scene is available");
    if (capturedFrames.empty()) {
        return false;
    }
    scene = capturedFrames.back();
    capturedFrames.clear();
    return true;
}

/// Observes both real top-level windows and the underlay in one continuous compositor capture.
static BOOL WINAPI PresentRecordedPanel(HDWP positions) {
    if (!observePanelSwaps || preparedPanel == nullptr) {
        return EndDeferWindowPos(positions);
    }
    Widget* replacement = preparedPanel;
    preparedPanel = nullptr;
    HWND previous = panelUnderTest->window;
    RECT oldCalendar = SceneCalendarBounds(panelUnderTest);
    FieldImage ready = ReadWindowSurface(replacement->window, false);
    CheckPanelSurface(replacement, ready);
    FieldImage oldScene;
    if (!TakePreviousPanelScene(oldScene)) {
        return EndDeferWindowPos(positions);
    }
    Check(SceneContainsPanel(panelUnderTest, oldScene, ReadWindowSurface(previous, false)),
        "scene capture includes the original real top-level widget over the checkerboard");
    const HWND controls[] = { replacement->calendarChild, replacement->analogChild,
        replacement->additionalAnalogChildren[0], replacement->additionalAnalogChildren[1] };
    for (HWND control : controls) {
        if (control != nullptr) {
            SetWindowSubclass(control, DelayNativeControlErase, 1, 0);
            RedrawWindow(control, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE);
        }
    }
    if (negativeSceneGap) {
        ShowWindow(previous, SW_HIDE);
        GdiFlush();
        PumpCaptureFor(80);
    }
    BOOL result = EndDeferWindowPos(positions);
    captureWindow = replacement->window;
    PumpCaptureFor(160);
    for (HWND control : controls) {
        if (control != nullptr) {
            RemoveWindowSubclass(control, DelayNativeControlErase, 1);
        }
    }
    Check(SameCompletePanelSurface(ready, ReadWindowSurface(replacement->window, false)),
        "native widget surface stays identical after presentation");
    std::lock_guard<std::mutex> lock(captureLock);
    Check(!capturedFrames.empty() && SUCCEEDED(captureFailure), "composite scene capture remains available");
    if (!capturedFrames.empty()) {
        FieldImage newScene = capturedFrames.back();
        RECT newCalendar = SceneCalendarBounds(replacement);
        bool complete = SceneContainsPanel(replacement, newScene, ready);
        Check(complete, "new scene includes every native client pixel at its configured opacity");
        std::vector<FieldImage> failed;
        for (const FieldImage& frame : capturedFrames) {
            comparedFrames++;
            if (!SamePanelScene(frame, oldScene, oldCalendar) && !SamePanelScene(frame, newScene, newCalendar)) {
                mismatchedFrames++;
                if (failed.size() < 4) {
                    failed.push_back(frame);
                }
            }
        }
        if (!failed.empty() || !complete) {
            failed.insert(failed.begin(), oldScene);
            failed.insert(failed.begin(), newScene);
            SaveFieldComparison(negativeSceneGap
                ? L"PanelRendering-deliberate-gap.bmp"
                : L"PanelRendering-failure.bmp", failed, 3);
        }
        if (preparedSwaps == 0) {
            std::wstring name = L"PanelRendering-scene-" + std::to_wstring(capturedVariant) + L".bmp";
            SaveFieldComparison(name.c_str(), std::vector<FieldImage>{ oldScene, newScene });
        }
    }
    preparedSwaps++;
    return result;
}

/// Exercises all native border transitions on actual top-level windows, using only test-owned covered or offscreen areas.
static int RunPanelCompositorTest() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    winrt::init_apartment(winrt::apartment_type::multi_threaded);
    hInstance = GetModuleHandleW(nullptr);
    INITCOMMONCONTROLSEX controls = {
        sizeof(controls),
        ICC_WIN95_CLASSES | ICC_DATE_CLASSES | ICC_LINK_CLASS | ICC_USEREX_CLASSES
    };
    InitCommonControlsEx(&controls);
    InitializeLanguageLocales();
    appLanguage = LANG_CS;
    LoadTimeZones();
    Check(RegisterApplicationTestWindowClass() != 0, "native application class");
    snapWidgetsToWorkArea = false;
    Widget widget;
    widget.config = CreateStoredWidgetDefaults(WIDGET_PANEL, 8100, LANG_CS, FONT_ANTIALIAS_CLEARTYPE);
    wchar_t variant[64] = {};
    GetEnvironmentVariableW(L"CALCLOCK_FRAME_TEST_VARIANT", variant, ARRAYSIZE(variant));
    int testVariant = _wtoi(variant);
    capturedVariant = testVariant;
    themesDisabled = testVariant / 2 % 2 != 0;
    const wchar_t* face = testVariant / 4 % 2 != 0 ? L"Cambria Math" : L"Segoe UI";
    widget.config.fontFace = face;
    widget.config.panelTopFont.face = face;
    widget.config.panelTimeFont.face = face;
    widget.config.panelBottomFont.face = face;
    for (AdditionalClockConfig& clock : widget.config.additionalClocks) {
        clock.enabled = testVariant / 8 != 0;
    }
    widget.config.opacity = testVariant % 2 != 0 ? 65 : 100;
    widget.config.visible = false;
    widget.config.showSeconds = false;
    SYSTEMTIME displayed = {};
    GetDisplayedTime(widget.config, &displayed);
    widget.config.offsetMilliseconds = (20LL - displayed.wSecond) * 1000 - displayed.wMilliseconds;
    widget.config.topMost = false;
    widget.config.borderStyle = DIGITAL_BORDER_3D;
    std::printf("Panel font=%ls themesDisabled=%d opacity=%d additional=%d\n", face, themesDisabled,
        widget.config.opacity, HasAdditionalClocks(widget.config));
    int width = 0;
    int height = 0;
    GetWidgetDimensions(widget.config, &width, &height);
    RECT covered = {};
    if (!FindCoveredCaptureArea(SIZE{ width + 16, height + 16 }, &covered)) {
        std::printf("INCONCLUSIVE: no completely covered test area; no test window was shown.\n");
        return 2;
    }
    WNDCLASSW sceneClass = {};
    sceneClass.lpfnWndProc = SceneWindowProc;
    sceneClass.hInstance = hInstance;
    sceneClass.lpszClassName = L"CalClock.CompositeSceneTest";
    Check(RegisterClassW(&sceneClass) != 0, "scene class registered");
    sceneWindow = CreateWindowExW(WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW, sceneClass.lpszClassName, L"", WS_POPUP,
        covered.left, covered.top, covered.right - covered.left, covered.bottom - covered.top, nullptr, nullptr,
        hInstance, nullptr);
    SetWindowPos(sceneWindow, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    RedrawWindow(sceneWindow, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
    wchar_t negative[16] = {};
    GetEnvironmentVariableW(L"CALCLOCK_FRAME_TEST_GAP", negative, ARRAYSIZE(negative));
    negativeSceneGap = _wtoi(negative) != 0;
    widget.config.x = covered.left + 8;
    widget.config.y = covered.top + 8;
    CreateWidgetWindow(&widget);
    captureWindow = widget.window;
    panelUnderTest = &widget;
    widget.config.visible = true;
    SetWindowPos(widget.window, HWND_BOTTOM, widget.config.x, widget.config.y, 0, 0,
        SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    SetWindowPos(sceneWindow, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    RenderWidget(&widget);
    RECT client = {};
    GetClientRect(widget.window, &client);
    int result = 2;
    try {
        CheckCaptureAreaCovered();
        winrt::check_hresult(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
            D3D11_CREATE_DEVICE_BGRA_SUPPORT, nullptr, 0, D3D11_SDK_VERSION, captureDevice.put(),
            nullptr, captureContext.put()));
        StartSceneCapture();
        observePanelSwaps = true;
        for (int source = 0; source < DIGITAL_BORDER_STYLE_COUNT; source++) {
            for (int target = 0; target < DIGITAL_BORDER_STYLE_COUNT; target++) {
                const int styles[] = { source, target };
                for (int style : styles) {
                    WidgetConfig appearance = widget.config;
                    appearance.borderStyle = style;
                    ApplyWidgetAppearancePreview(&widget, appearance, false);
                    RECT actual = {};
                    GetClientRect(widget.window, &actual);
                    Check(EqualRect(&client, &actual),
                        "every native frame style preserves the font-dependent client size");
                }
            }
        }
        observePanelSwaps = false;
        Check(preparedSwaps >= 24, "all frame styles pass through prepared native window swaps");
        Check(mismatchedFrames == 0 && comparedFrames >= preparedSwaps,
            "every composite scene shows either the complete previous widget or the complete new widget");
        std::printf("PANEL prepared=%d frames=%d mismatched=%d\n", preparedSwaps, comparedFrames, mismatchedFrames);
        if (negativeSceneGap && mismatchedFrames > 0 && failures == 1) {
            std::printf("SCENE_GAP_DETECTED: the deliberate whole-window disappearance was rejected.\n");
        }
        result = failures == 0 ? 0 : 1;
    } catch (const winrt::hresult_error& error) {
        std::printf("INCONCLUSIVE: native capture unavailable: %lX %ls\n",
            static_cast<HRESULT>(error.code()), error.message().c_str());
    }
    observePanelSwaps = false;
    if (sceneSession != nullptr) {
        sceneSession.Close();
        scenePool.FrameArrived(sceneToken);
        scenePool.Close();
    }
    DestroyWidgetWindow(&widget);
    DestroyWindow(sceneWindow);
    UnregisterClassW(L"CalClock.CompositeSceneTest", hInstance);
    panelUnderTest = nullptr;
    ShutdownAnalogClockHost();
    UnregisterClassW(CLASS_NAME, hInstance);
    return result;
}

/// Starts an isolated test worker and returns its exit status without opening a console or activating a window.
static int RunPanelTestWorker() {
    wchar_t executable[MAX_PATH] = {};
    GetModuleFileNameW(nullptr, executable, ARRAYSIZE(executable));
    std::wstring command = L"\"" + std::wstring(executable) + L"\" --worker";
    STARTUPINFOW startup = { sizeof(startup) };
    startup.dwFlags = STARTF_USESTDHANDLES;
    startup.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    startup.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    startup.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    PROCESS_INFORMATION process = {};
    if (!CreateProcessW(executable, command.data(), nullptr, nullptr, TRUE, CREATE_NO_WINDOW,
        nullptr, nullptr, &startup, &process)) {
        return 2;
    }
    DWORD result = 2;
    if (WaitForSingleObject(process.hProcess, 60000) == WAIT_OBJECT_0) {
        GetExitCodeProcess(process.hProcess, &result);
    } else {
        TerminateProcess(process.hProcess, 2);
        WaitForSingleObject(process.hProcess, 5000);
        std::printf("INCONCLUSIVE: test worker exceeded its time limit.\n");
    }
    CloseHandle(process.hThread);
    CloseHandle(process.hProcess);
    return static_cast<int>(result);
}

/// Captures only an inactive test-owned widget without opening a console or activating other applications.
int main(int argc, char** argv) {
    if (argc == 2 && strcmp(argv[1], "--worker") == 0) {
        return RunPanelCompositorTest();
    }
    return RunPanelTestWorker();
}
