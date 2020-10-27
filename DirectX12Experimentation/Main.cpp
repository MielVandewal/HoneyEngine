#include <Application.h>

int main()
{
	HoneyEngine::Application temp;
	temp.Initialize("Test", 1920, 1080);
	temp.Run();
}