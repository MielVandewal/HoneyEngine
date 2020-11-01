#include "Window.h"
#include "GameContext.h"

HoneyEngine::Window::Window(HINSTANCE hInstance, const LPCWSTR& name, const int width, const int height)
    : m_WindowWidth(width)
    , m_WindowHeight(height)
    , m_IsInitialized(false)
    , m_Hwnd(0)
{
    Initialize(hInstance, name);
}

void HoneyEngine::Window::Initialize(HINSTANCE hInstance, const LPCWSTR& name)
{
    if (m_IsInitialized)
        return;

    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = NULL;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = name;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Error registering class", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    m_Hwnd = CreateWindowEx(NULL, name, name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, m_WindowWidth, m_WindowHeight, NULL, NULL, hInstance, NULL);

    if (!m_Hwnd)
    {
        MessageBox(NULL, L"Error creating window", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    ShowWindow(m_Hwnd, true);
    UpdateWindow(m_Hwnd);

    Microsoft::WRL::ComPtr<ID3D12Device2> pDevice = GameContext::GetInstance()->pDevice;

    CreateSwapChain();
    CreateDescriptorHeap();
    m_RTVDescriptorSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    UpdateRenderTargetView();
    CreateCommandAllocator();
    CreateCommandList();

    m_IsInitialized = true;
}

LRESULT HoneyEngine::Window::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

void HoneyEngine::Window::CreateSwapChain()
{
    using namespace Microsoft::WRL;

    ComPtr<IDXGIFactory4> dxgiFactory4;
    UINT createFactoryFlags = 0;

#if defined(_DEBUG)
    createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

    ThrowIfFailed(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory4)));

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.Width = m_WindowWidth;
    swapChainDesc.Height = m_WindowHeight;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.Stereo = FALSE;
    swapChainDesc.SampleDesc = { 1, 0 };
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = m_BufferCount;
    swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    // It is recommended to always allow tearing if tearing support is available.
    swapChainDesc.Flags = CheckTearingSupport() ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;

    ComPtr<IDXGISwapChain1> swapChain1;
    ThrowIfFailed(dxgiFactory4->CreateSwapChainForHwnd( GameContext::GetInstance()->pCommandQueue.Get(), m_Hwnd,
        &swapChainDesc, nullptr, nullptr, &swapChain1));

    // Disable the Alt+Enter fullscreen toggle feature. Switching to fullscreen
    // will be handled manually.
    ThrowIfFailed(dxgiFactory4->MakeWindowAssociation(m_Hwnd, DXGI_MWA_NO_ALT_ENTER));

    ThrowIfFailed(swapChain1.As(&m_pSwapChain));
}

void HoneyEngine::Window::CreateDescriptorHeap()
{
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
    desc.NumDescriptors = m_BufferCount;
    desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

    ThrowIfFailed(GameContext::GetInstance()->pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_pRTVDescriptorHeap)));
}

void HoneyEngine::Window::CreateCommandAllocator()
{
    Microsoft::WRL::ComPtr<ID3D12Device2> pDevice = GameContext::GetInstance()->pDevice;
    for (int i = 0; i < m_BufferCount; ++i)
    {
        ThrowIfFailed(pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT
            , IID_PPV_ARGS(&m_pCommandAllocators[i])));
    }
}

void HoneyEngine::Window::CreateCommandList()
{
    ThrowIfFailed(GameContext::GetInstance()->pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT
        , m_pCommandAllocators[m_pSwapChain->GetCurrentBackBufferIndex()].Get(), nullptr, IID_PPV_ARGS(&m_pCommandList)));
    ThrowIfFailed(m_pCommandList->Close());
}

void HoneyEngine::Window::UpdateRenderTargetView()
{
    Microsoft::WRL::ComPtr<ID3D12Device2> pDevice = GameContext::GetInstance()->pDevice;
    auto rtvDescriptorSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_pRTVDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

    for (int i = 0; i < m_BufferCount; ++i)
    {
        Microsoft::WRL::ComPtr<ID3D12Resource> backBuffer;
        ThrowIfFailed(m_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&backBuffer)));

        pDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, rtvHandle);
        m_pBackBuffers[i] = backBuffer;
        rtvHandle.Offset(rtvDescriptorSize);
    }
}

bool HoneyEngine::Window::CheckTearingSupport()
{
    using namespace Microsoft::WRL;

    BOOL allowTearing = FALSE;

    // Rather than create the DXGI 1.5 factory interface directly, we create the
    // DXGI 1.4 interface and query for the 1.5 interface. This is to enable the 
    // graphics debugging tools which will not support the 1.5 factory interface 
    // until a future update.
    ComPtr<IDXGIFactory4> factory4;
    if (SUCCEEDED(CreateDXGIFactory1(IID_PPV_ARGS(&factory4))))
    {
        ComPtr<IDXGIFactory5> factory5;
        if (SUCCEEDED(factory4.As(&factory5)))
        {
            if (FAILED(factory5->CheckFeatureSupport(
                DXGI_FEATURE_PRESENT_ALLOW_TEARING,
                &allowTearing, sizeof(allowTearing))))
            {
                allowTearing = FALSE;
            }
        }
    }

    return allowTearing == TRUE;
}