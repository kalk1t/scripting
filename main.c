#include <windows.h>


#include "include/define.h"
#include "include/functions.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    switch (uMsg) {

    case WM_CREATE:
    {
        loadBitmaps();
        text_window(hwnd);
		encrypted_text_window(hwnd);
		decrypted_text_window(hwnd);



        return 0;
    }

    case WM_COMMAND:
    {
        switch ((short)(wParam)) {
            case generate:
            {
                int length = GetWindowTextLength(hText);
                char* buffer = (char*)malloc(length + 1);
                SendDlgItemMessageA(hwnd, plain_text, WM_GETTEXT, length, (LPARAM)buffer);
                SendDlgItemMessageA(hwnd, encrypted_text, WM_SETTEXT, 0, (LPARAM)buffer);
                SendDlgItemMessageA(hwnd, decrypted_text, WM_SETTEXT, 0, (LPARAM)buffer);

                free(buffer);
            }
            break;
            case clear:
            {
                SendDlgItemMessageA(hwnd, plain_text, WM_SETTEXT, 0, 0);
                SendDlgItemMessageA(hwnd, encrypted_text, WM_SETTEXT, 0, 0);
                SendDlgItemMessageA(hwnd, decrypted_text, WM_SETTEXT, 0, 0);
            }
            break;
        }
		return 0;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

		HDC hMemDC = CreateCompatibleDC(hdc);
        SelectObject(hMemDC, background_bm);
		BitBlt(hdc, 0, 0, 900, 900, hMemDC, 0, 0, SRCCOPY);

        DeleteDC(hMemDC); // Clean up the memory device context
        EndPaint(hwnd, &ps);
        return 0;
    }

	case WM_DESTROY:
		// Clean up resources before exiting


		DeleteDC(GetDC(hwnd)); // Clean up the device context
		DeleteObject(background_bm); // Clean up the bitmap
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"MyWindowClass";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = NULL; // We fully handle background ourselves
    wc.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Scripting",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        (GetSystemMetrics(SM_CXSCREEN) - 900) / 2,
        (GetSystemMetrics(SM_CYSCREEN) - 900) / 2,
        900,
        900,
        NULL, NULL, hInstance, NULL
    );

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
