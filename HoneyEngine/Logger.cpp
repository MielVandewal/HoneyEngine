#include "Logger.h"

void HoneyEngine::Logger::LogInfo(const std::wstring& message, bool includeTimestamp)
{
	if (includeTimestamp)
		LogTimestamp();
    OutputDebugStringW((L"[INFO]:   " + message + L"\n").c_str());
}

void HoneyEngine::Logger::LogWarning(const std::wstring& message, bool includeTimestamp)
{
	if (includeTimestamp)
		LogTimestamp();
    OutputDebugStringW((L"[WARNING]:   " + message + L"\n").c_str());
}

void HoneyEngine::Logger::LogError(const std::wstring& message, bool includeTimestamp)
{
	if (includeTimestamp)
		LogTimestamp();
    OutputDebugStringW((L"[ERROR]:   " + message + L"\n").c_str());
    MessageBox(0, message.c_str(), L"ERROR", 0);
}

void HoneyEngine::Logger::LogTimestamp()
{
	SYSTEMTIME st;
	GetSystemTime(&st);

	std::wstringstream stream;
	stream << L"[" << (st.wHour + 1) % 24 << L":" << st.wMinute << L":" << st.wSecond << L":" << st.wMilliseconds << L"]";
	OutputDebugStringW(stream.str().c_str());
}
