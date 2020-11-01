#pragma once
#include "HoneyEnginePCH.h"
#include "GameContext.h"

namespace HoneyEngine
{
	class Application
	{
	public:
        Application(bool useWarp)
            : m_UseWarp(useWarp)
        {};
        ~Application() {};
        void Initialize(HINSTANCE hInstance, const LPCWSTR& name, const int width, const int height);
        void Cleanup();
        void Run();

    private:
        Microsoft::WRL::ComPtr<IDXGIAdapter4> GetAdapter();
        Microsoft::WRL::ComPtr<ID3D12Device2> CreateDevice(); 
        Microsoft::WRL::ComPtr<ID3D12CommandQueue> CreateCommandQueue();

        static const float m_SecPerFrame;
        const bool m_UseWarp;
	};
}

