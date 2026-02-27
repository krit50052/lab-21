#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

HWND text1, text2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
        case WM_CREATE: {
            text1 = CreateWindow("edit", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 25, 20, 180, 20, hwnd, NULL, NULL, NULL);
            text2 = CreateWindow("edit", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 25, 50, 180, 20, hwnd, NULL, NULL, NULL);

            CreateWindow("button", "+", WS_VISIBLE | WS_CHILD | WS_BORDER, 25,  80, 40, 30, hwnd, (HMENU)1, NULL, NULL);
            CreateWindow("button", "-", WS_VISIBLE | WS_CHILD | WS_BORDER, 70,  80, 40, 30, hwnd, (HMENU)2, NULL, NULL);
            CreateWindow("button", "*", WS_VISIBLE | WS_CHILD | WS_BORDER, 115, 80, 40, 30, hwnd, (HMENU)3, NULL, NULL);
            CreateWindow("button", "/", WS_VISIBLE | WS_CHILD | WS_BORDER, 160, 80, 40, 30, hwnd, (HMENU)4, NULL, NULL);
            break;
        }

        case WM_COMMAND: {
            int command = LOWORD(wParam);

            if(command >= 1 && command <= 4) {
                char buf1[256], buf2[256]; // ✅ แก้จาก char เป็น char array
                
                GetWindowText(text1, buf1, 256);
                GetWindowText(text2, buf2, 256);

                double num1 = atof(buf1);
                double num2 = atof(buf2);
                double result = 0;

                switch(command) {
                    case 1: result = num1 + num2; break;
                    case 2: result = num1 - num2; break;
                    case 3: result = num1 * num2; break;
                    case 4:
                        if(num2 != 0) {
                            result = num1 / num2;
                        } else {
                            MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_ICONEXCLAMATION | MB_OK);
                            return 0;
                        }
                        break;
                }

                char resBuf[256]; // ✅ แก้จาก char เป็น char array
                sprintf(resBuf, "%g", result);
                MessageBox(hwnd, resBuf, "Result", MB_OK);
            }
            break;
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }

        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc, 0, sizeof(wc));
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(0, 255, 255)); // ฟ้า Cyan
    wc.lpszClassName = "WindowClass";
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "My Calculator",
        WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX, // ✅ ล็อกไม่ให้ขยาย (ไม่มี WS_THICKFRAME)
        CW_USEDEFAULT, CW_USEDEFAULT,
        250, 200,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    while(GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}