#pragma once
#include "HoneyEnginePCH.h"

namespace HoneyEngine
{
	class Application
	{
	public:
        void Initialize(const std::string name, const int width, const int height);
        void Cleanup();
        void Run();

    private:
        static const float m_SecPerFrame;
	};
}

