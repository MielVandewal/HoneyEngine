#pragma once
#include "HoneyEnginePCH.h"

namespace HoneyEngine
{
    class Window final
    {
    public:
        Window(HINSTANCE hInstance, const LPCWSTR& name, const int width, const int height);
        ~Window();
        void Initialize(HINSTANCE hInstance, const LPCWSTR& name);

        void Render();
        uint64_t Signal();
        void Flush();

        HWND GetWindowHandle() const { return m_Hwnd; }
        const float GetAspectRatio() const { return float(m_WindowWidth) / m_WindowHeight; }
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

        bool IsFenceComplete(uint64_t fenceValue);
        void WaitForFenceValue(uint64_t fenceValue);

        static const int m_BufferCount = 3;

        Microsoft::WRL::ComPtr<IDXGISwapChain4> m_pSwapChain;
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_pCommandList;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_pRTVDescriptorHeap;
        Microsoft::WRL::ComPtr<ID3D12Resource> m_pBackBuffers[m_BufferCount];
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_pCommandAllocators[m_BufferCount];
        Microsoft::WRL::ComPtr<ID3D12Fence> m_Fence;

        HANDLE m_FenceEvent;
        uint64_t m_FrameFenceValues[m_BufferCount] = {};
        uint64_t m_FenceValue;
        UINT m_RTVDescriptorSize;

        const int m_WindowWidth;
        const int m_WindowHeight;
        bool m_IsInitialized;
        bool m_IsTearingSupported;
        bool m_VSync = false;
        HWND m_Hwnd;
    };
}
