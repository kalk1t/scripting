#include <windows.h>

HBRUSH hBackgroundBrush;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {

    case WM_CREATE:
        hBackgroundBrush = CreateSolidBrush(RGB(0, 213, 0));
        return 0;

    case WM_ERASEBKGND:
    {
        HDC hdc = (HDC)wParam;
        RECT rc;
        GetClientRect(hwnd, &rc);
        FillRect(hdc, &rc, hBackgroundBrush);
        return 1; // Tell Windows: we painted the background
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, hBackgroundBrush);
        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        DeleteObject(hBackgroundBrush);
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"MyWindowClass";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = NULL; // We fully handle background ourselves
    wc.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wc);

    int w = 900;
    int h = 900;
    int x = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Scripting",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        x, y, w, h,
        NULL, NULL, hInstance, NULL
    );

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
