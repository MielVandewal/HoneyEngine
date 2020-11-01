#pragma once
#include "HoneyEnginePCH.h"
#include "GameContext.h"

namespace HoneyEngine
{
	class Application
	{
	public:
        void Initialize(HINSTANCE hInstance, const LPCWSTR& name, const int width, const int height, const bool useWarp = false);
        void Cleanup();
        void Run();

    private:
        Microsoft::WRL::ComPtr<IDXGIAdapter4> GetAdapter();
        Microsoft::WRL::ComPtr<ID3D12Device2> CreateDevice(); 
        Microsoft::WRL::ComPtr<ID3D12CommandQueue> CreateCommandQueue();
        void EnableDebugLayer();

        static const float m_SecPerFrame;
        bool m_UseWarp;
	};
}

