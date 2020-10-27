#include "Application.h"
#include "SceneManager.h"
#include "InputManager.h"

const float HoneyEngine::Application::m_SecPerFrame = 0.016f;

void HoneyEngine::Application::Initialize(const std::string name, const int width, const int height)
{
	InputManager::GetInstance()->Initialize(); 
}

void HoneyEngine::Application::Run()
{
    bool doContinue = true;
    float lag = 0.0f;
    auto lastTime = std::chrono::high_resolution_clock::now();

    while (doContinue)
    {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;
        lag += deltaTime;
        SceneManager::GetInstance()->Update(deltaTime);
        while (lag >= m_SecPerFrame)
        {
            InputManager::GetInstance()->Update();
            SceneManager::GetInstance()->FixedUpdate(m_SecPerFrame);
            lag -= m_SecPerFrame;

            if (InputManager::GetInstance()->IsKeyDown(VK_ESCAPE))
                doContinue = false;
        }
        SceneManager::GetInstance()->Render();

    }

    Cleanup();
}

void HoneyEngine::Application::Cleanup()
{
    SceneManager::Release();
    InputManager::Release();
}