#include <windows.h>
#include <stdio.h>

#include "../include/define.h"
#include "../include/functions.h"

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
        case encrypt:
        {
            int text_length = GetWindowTextLength(hText);
            int key_length = GetWindowTextLength(hKey);
            int key_integer = 1;
            char* text_buffer = (char*)malloc(text_length + 1);
            char* key_buffer = (char*)malloc(key_length + 1);


            SendDlgItemMessageA(hwnd, plain_text, WM_GETTEXT, text_length + 1, (LPARAM)text_buffer);
            SendDlgItemMessageA(hwnd, key, WM_GETTEXT, key_length + 1, (LPARAM)key_buffer);
            if (key_buffer != NULL) {
               key_integer = atoi(key_buffer);
            }

            int* asci_array_of_text_buffer = convert_text_to_asci(text_buffer, text_length,key_integer);
            int* encrypted_text_buffer_to_int = cipher_text_to_int_with_key(asci_array_of_text_buffer, text_length, key_integer);
            unsigned char* encrypt_text_buffer_to_char = encrypt_from_asci_to_char_with_key(encrypted_text_buffer_to_int, text_length);
            SendDlgItemMessageA(hwnd, encrypted_text, WM_SETTEXT, 0, (LPARAM)(char*)encrypt_text_buffer_to_char);
            unsigned char* decrypted_text_buffer_to_char = decrypt_from_asci_to_char_with_key(encrypted_text_buffer_to_int, text_length, key_integer);
            SendDlgItemMessageA(hwnd, decrypted_text, WM_SETTEXT, 0, (LPARAM)decrypted_text_buffer_to_char);

            free(text_buffer);
            free(key_buffer);
            free(asci_array_of_text_buffer);
            free(encrypted_text_buffer_to_int);
            free(encrypt_text_buffer_to_char);
            free(decrypted_text_buffer_to_char);
        }
        break;
        case decrypt:
        {
            int text_length = GetWindowTextLength(hText);
            int key_length = GetWindowTextLength(hKey);
            int key_integer = 1;
            char* text_buffer = (char*)malloc(text_length + 1);
            char* key_buffer = (char*)malloc(key_length + 1);


            SendDlgItemMessageA(hwnd, plain_text, WM_GETTEXT, text_length + 1, (LPARAM)text_buffer);
            SendDlgItemMessageA(hwnd, key, WM_GETTEXT, key_length + 1, (LPARAM)key_buffer);
            if (key_buffer != NULL) {
                key_integer = atoi(key_buffer);
            }
            key_integer = -key_integer;
            int* asci_array_of_text_buffer = convert_text_to_asci(text_buffer, text_length, key_integer);
            int* encrypted_text_buffer_to_int = cipher_text_to_int_with_key(asci_array_of_text_buffer, text_length, key_integer);
            unsigned char* encrypt_text_buffer_to_char = encrypt_from_asci_to_char_with_key(encrypted_text_buffer_to_int, text_length);
            SendDlgItemMessageA(hwnd, encrypted_text, WM_SETTEXT, 0, (LPARAM)(char*)encrypt_text_buffer_to_char);
            unsigned char* decrypted_text_buffer_to_char = decrypt_from_asci_to_char_with_key(encrypted_text_buffer_to_int, text_length, key_integer);
            SendDlgItemMessageA(hwnd, decrypted_text, WM_SETTEXT, 0, (LPARAM)decrypted_text_buffer_to_char);

            free(text_buffer);
            free(key_buffer);
            free(asci_array_of_text_buffer);
            free(encrypted_text_buffer_to_int);
            free(encrypt_text_buffer_to_char);
            free(decrypted_text_buffer_to_char);
        }
        break;
        case clear:
        {
            SendDlgItemMessageA(hwnd, plain_text, WM_SETTEXT, 0, 0);
            SendDlgItemMessageA(hwnd, encrypted_text, WM_SETTEXT, 0, 0);
            SendDlgItemMessageA(hwnd, decrypted_text, WM_SETTEXT, 0, 0);
            SendDlgItemMessageA(hwnd, key, WM_SETTEXT, 0, 0);
        }
        break;
        case copy:
        {
            int length = GetWindowTextLength(hEncryptedText);
            if (length > 0) {
                char* buffer = (char*)GlobalAlloc(GMEM_MOVEABLE, length + 1);
                if (buffer) {
                    char* text = (char*)GlobalLock(buffer);
                    SendDlgItemMessageA(hwnd, encrypted_text, WM_GETTEXT, length + 1, (LPARAM)text);
                    GlobalUnlock(buffer);
                    // Open clipboard and copy text
                    if (OpenClipboard(hwnd)) {
                        EmptyClipboard();
                        SetClipboardData(CF_TEXT, buffer);
                        CloseClipboard();
                    }

                }
            }
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
        char Text[] = "Text";
        char Key[] = "Key";
		char EncryptedText[] = "Encrypted text";
		char DecryptedText[] = "Decrypted text";
        TextOutA(hdc, 50, 80, Text, sizeof(Text));
        TextOutA(hdc, 50, 280, EncryptedText, sizeof(EncryptedText));
        TextOutA(hdc, 50, 480, DecryptedText, sizeof(DecryptedText));
        TextOutA(hdc, 600, 15, Key, sizeof(Key));
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
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Set a default cursor

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
