#pragma once
#include "HoneyEnginePCH.h"

namespace HoneyEngine
{
    class Window final
    {
    public:
        Window(HINSTANCE hInstance, const LPCWSTR& name, const int width, const int height);
        ~Window() = delete;
        void Initialize(HINSTANCE hInstance, const LPCWSTR& name);

        HWND GetWindowHandle() const { return m_Hwnd; }
        const int GetWindowWidth() const { return m_WindowWidth; }
        const int GetWindowHeight() const { return m_WindowHeight; }
        static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    private:
        void CreateSwapChain();
        void CreateDescriptorHeap();
        void CreateCommandAllocator();
        void CreateCommandList();
        void UpdateRenderTargetView();
        bool CheckTearingSupport();

        static const int m_BufferCount = 3;

        Microsoft::WRL::ComPtr<IDXGISwapChain4> m_pSwapChain;
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_pCommandList;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_pRTVDescriptorHeap;
        Microsoft::WRL::ComPtr<ID3D12Resource> m_pBackBuffers[m_BufferCount];
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_pCommandAllocators[m_BufferCount];

        UINT m_RTVDescriptorSize;

        const int m_WindowWidth;
        const int m_WindowHeight;
        bool m_IsInitialized;
        HWND m_Hwnd;
    };
}
