#pragma once
#include "HoneyEnginePCH.h"
#include "Singleton.h"
#include "Window.h"

namespace HoneyEngine
{
	class GameContext final : public Singleton<GameContext>
	{
	public:
		GameContext() = default;
		~GameContext() { SafeDelete(pWindow); }

		Window* pWindow = nullptr;
		Microsoft::WRL::ComPtr<ID3D12Device2> pDevice;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> pCommandQueue;
	};
}