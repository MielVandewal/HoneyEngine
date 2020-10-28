#pragma once
#include "HoneyEnginePCH.h"
#include "Singleton.h"

namespace HoneyEngine
{
    class Window final : public Singleton<Window>
    {
    public:
        Window();
        ~Window() = delete;
        void Initialize(HINSTANCE hInstance, const LPCWSTR& name, const int width, const int height);

        HWND GetWindowHandle() const { return m_Hwnd; }
        const int GetWindowWidth() const { return m_WindowWidth; }
        const int GetWindowHeight() const { return m_WindowHeight; }
        static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    private:
        bool m_IsInitialized;
        const int m_WindowWidth;
        const int m_WindowHeight;
        HWND m_Hwnd;
    };
}
