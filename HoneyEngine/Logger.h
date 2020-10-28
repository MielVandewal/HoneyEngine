#pragma once
#include "HoneyEnginePCH.h"
#include "Singleton.h"

namespace HoneyEngine
{
	class Logger final : public Singleton<Logger>
	{
	public:
		Logger() = default;
		~Logger() = default;

		void LogInfo(const std::wstring& message, bool includeTimestamp = false);
		void LogWarning(const std::wstring& message, bool includeTimestamp = false);
		void LogError(const std::wstring& message, bool includeTimestamp = false);

	private:
		void LogTimestamp();
	};
}