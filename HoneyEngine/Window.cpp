#include "Window.h"

HoneyEngine::Window::Window()
    : m_WindowWidth(0)
    , m_WindowHeight(0)
    , m_IsInitialized(false)
{
}

void HoneyEngine::Window::Initialize(HINSTANCE hInstance, const LPCWSTR& name, const int width, const int height)
{
    if (m_IsInitialized)
        return;

    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = NULL;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = name;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Error registering class", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    m_Hwnd = CreateWindowEx(NULL, name, name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL);

    if (!m_Hwnd)
    {
        MessageBox(NULL, L"Error creating window", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    ShowWindow(m_Hwnd, true);
    UpdateWindow(m_Hwnd);

    const_cast<int&>(m_WindowWidth) = width;
    const_cast<int&>(m_WindowHeight) = height;
    m_IsInitialized = true;
}

LRESULT HoneyEngine::Window::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}