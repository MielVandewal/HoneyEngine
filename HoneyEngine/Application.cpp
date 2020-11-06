#include "Application.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Logger.h"
#include "Window.h"

const float HoneyEngine::Application::m_SecPerFrame = 0.016f;

void HoneyEngine::Application::Initialize(HINSTANCE hInstance, const LPCWSTR& name, const int width, const int height, const bool useWarp)
{
    EnableDebugLayer();
    m_UseWarp = useWarp;

    InputManager::GetInstance()->Initialize();

    GameContext* gameContext = GameContext::GetInstance();
    gameContext->pDevice = CreateDevice();
    gameContext->pCommandQueue = CreateCommandQueue();
    gameContext->pWindow = new Window(hInstance, name, width, height);
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
        SceneManager::GetInstance()->Update();
        while (lag >= m_SecPerFrame)
        {
            InputManager::GetInstance()->Update();
            SceneManager::GetInstance()->FixedUpdate();
            lag -= m_SecPerFrame;

            if (InputManager::GetInstance()->IsKeyDown(VK_ESCAPE))
                doContinue = false;
        }
        SceneManager::GetInstance()->Render();
        GameContext::GetInstance()->pWindow->Render();

    }

    Cleanup();
}

void HoneyEngine::Application::Cleanup()
{
    SceneManager::Release();
    InputManager::Release();
    GameContext::Release();
    Logger::Release();
}

Microsoft::WRL::ComPtr<IDXGIAdapter4> HoneyEngine::Application::GetAdapter()
{
    using namespace Microsoft::WRL;
    ComPtr<IDXGIFactory4> dxgiFactory;
    UINT createFactoryFlags = 0;
#if defined(_DEBUG)
    createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

    ThrowIfFailed(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory)));

    ComPtr<IDXGIAdapter1> dxgiAdapter1;
    ComPtr<IDXGIAdapter4> dxgiAdapter4;

    if (m_UseWarp)
    {
        ThrowIfFailed(dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&dxgiAdapter1)));
        ThrowIfFailed(dxgiAdapter1.As(&dxgiAdapter4));
    }
    else
    {
        SIZE_T maxDedicatedVideoMemory = 0;
        for (UINT i = 0; dxgiFactory->EnumAdapters1(i, &dxgiAdapter1) != DXGI_ERROR_NOT_FOUND; ++i)
        {
            DXGI_ADAPTER_DESC1 dxgiAdapterDesc1;
            dxgiAdapter1->GetDesc1(&dxgiAdapterDesc1);

            // Check to see if the adapter can create a D3D12 device without actually 
            // creating it. The adapter with the largest dedicated video memory
            // is favored.
            if ((dxgiAdapterDesc1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == 0 &&
                SUCCEEDED(D3D12CreateDevice(dxgiAdapter1.Get(),
                    D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr)) &&
                dxgiAdapterDesc1.DedicatedVideoMemory > maxDedicatedVideoMemory)
            {
                maxDedicatedVideoMemory = dxgiAdapterDesc1.DedicatedVideoMemory;
                ThrowIfFailed(dxgiAdapter1.As(&dxgiAdapter4));
            }
        }
    }

    return dxgiAdapter4;
}

Microsoft::WRL::ComPtr<ID3D12Device2> HoneyEngine::Application::CreateDevice()
{
    using namespace Microsoft::WRL;
    ComPtr<ID3D12Device2> d3d12Device2;
    ThrowIfFailed(D3D12CreateDevice(GetAdapter().Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&d3d12Device2)));

    // Enable debug messages in debug mode.
#if defined(_DEBUG)
    ComPtr<ID3D12InfoQueue> pInfoQueue;
    if (SUCCEEDED(d3d12Device2.As(&pInfoQueue)))
    {
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, TRUE);

        // Suppress messages based on their severity level
        D3D12_MESSAGE_SEVERITY Severities[] =
        {
            D3D12_MESSAGE_SEVERITY_INFO
        };

        // Suppress individual messages by their ID
        D3D12_MESSAGE_ID DenyIds[] = 
        {
            D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,  
            D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,                        
            D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE,                      
        };

        D3D12_INFO_QUEUE_FILTER newFilter = {};
        newFilter.DenyList.NumSeverities = _countof(Severities);
        newFilter.DenyList.pSeverityList = Severities;
        newFilter.DenyList.NumIDs = _countof(DenyIds);
        newFilter.DenyList.pIDList = DenyIds;

        ThrowIfFailed(pInfoQueue->PushStorageFilter(&newFilter));
    }
#endif

    return d3d12Device2;
}

Microsoft::WRL::ComPtr<ID3D12CommandQueue> HoneyEngine::Application::CreateCommandQueue()
{
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> d3d12CommandQueue;

    D3D12_COMMAND_QUEUE_DESC desc = {};
    desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    desc.NodeMask = 0;

    ThrowIfFailed(GameContext::GetInstance()->pDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(&d3d12CommandQueue)));

    return d3d12CommandQueue;
}

void HoneyEngine::Application::EnableDebugLayer()
{
#if defined(_DEBUG)
    // Always enable the debug layer before doing anything DX12 related
    // so all possible errors generated while creating DX12 objects
    // are caught by the debug layer.
    Microsoft::WRL::ComPtr<ID3D12Debug> debugInterface;
    ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface)));
    debugInterface->EnableDebugLayer();
#endif
}
