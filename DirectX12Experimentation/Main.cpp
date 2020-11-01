#include <Application.h>

//int main()
//{
//	HoneyEngine::Application temp;
//	temp.Initialize("Test", 1920, 1080);
//	temp.Run();
//}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
    HoneyEngine::Application temp{ false };
    temp.Initialize(hInstance, L"HoneyEngine", 1080, 720);
    temp.Run();

    return 0;
}