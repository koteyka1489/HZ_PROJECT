#include "Graphics.h"
#include "imgui\imgui_impl_dx11.h"
#include "imgui\imgui_impl_win32.h"



Graphics::Graphics(HWND hWnd)
{

    RECT rect;
    GetClientRect(hWnd, &rect);
    UINT width = rect.right - rect.left;
    UINT height = rect.bottom - rect.top;

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    sd.BufferDesc.RefreshRate.Denominator = 0;
    sd.BufferDesc.RefreshRate.Numerator = 0;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 2;
    sd.OutputWindow = hWnd;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    sd.Flags = 0;

    UINT swapCreateFlags = 0u;
#ifndef NDEBUG
    swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        swapCreateFlags,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &sd,
        &pSwap,
        &pDevice,
        nullptr,
        &pContext
    );
    THROW_COM_ERROR_GFX_INFO(hr, "ERROR CREATE DEVICE");

    ComPtr<ID3D11Resource> pBackBuffer;
    hr = pSwap->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
    THROW_COM_ERROR_GFX_INFO(hr, "ERROR Get Buffer");

    hr = pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget);
    THROW_COM_ERROR_GFX_INFO(hr, "ERROR CREATE Render Target View");

    // Create Depth Stencil View
    D3D11_DEPTH_STENCIL_DESC dsDesc = {};
    dsDesc.DepthEnable = TRUE;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
    ComPtr<ID3D11DepthStencilState> pDSState;
    hr = pDevice->CreateDepthStencilState(&dsDesc, &pDSState);
    THROW_COM_ERROR_GFX_INFO(hr, "CreateDepthStencilState");

    pContext->OMSetDepthStencilState(pDSState.Get(), 1u);

    ComPtr<ID3D11Texture2D> pDepthStencil;
    D3D11_TEXTURE2D_DESC descDepth = {};
    descDepth.Width = width;
    descDepth.Height = height;
    descDepth.MipLevels = 1u;
    descDepth.ArraySize = 1u;
    descDepth.Format = DXGI_FORMAT_D32_FLOAT;
    descDepth.SampleDesc.Count = 1u;
    descDepth.SampleDesc.Quality = 0u;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0u;
    descDepth.MiscFlags = 0u;

    hr = pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);
    THROW_COM_ERROR_GFX_INFO(hr, "CreateTexture2D");

    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
    descDSV.Format = DXGI_FORMAT_D32_FLOAT;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0u;

    hr = pDevice->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &pDSV);
    THROW_COM_ERROR_GFX_INFO(hr, "CreateDepthStencilView");

    // Create ViewPort
    D3D11_VIEWPORT vp;
    vp.Width = static_cast<float>(width);
    vp.Height = static_cast<float>(height);
    vp.MinDepth = 0.f;
    vp.MaxDepth = 1.f;
    vp.TopLeftX = 0.f;
    vp.TopLeftY = 0.f;

    pContext->RSSetViewports(1u, &vp);

    projection = DirectX::XMMatrixPerspectiveLH(1.f, 3.f / 4.f, 0.5f, 1000.f);


    // init imgui
    ImGui_ImplDX11_Init(pDevice.Get(), pContext.Get());
    
}

Graphics::~Graphics()
{
    ImGui_ImplDX11_Shutdown();
    pDevice->Release();
    pContext->Release();
    pSwap->Release();
    pTarget->Release();
    pDSV->Release();

}




void Graphics::EndFrame()
{
#ifndef NDEBUG
	infoManager.Set();
#endif
	hr = pSwap->Present(1u, 0u);
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR pSwap Present");
}

void Graphics::BeginFrame(float red, float green, float blue)
{
    const float color[] = { red, green, blue, 1.0f };
    // Очистка буфера кадра (цветного буфера) заданным цветом. 
    pContext->ClearRenderTargetView(pTarget.Get(), color);

    // Очистка буфера глубины и трафарета. 
    pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);

    // Установка целевого рендеринга и буфера глубины-трафарета для выходного модуля (output merger).
    pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), pDSV.Get());

    ImguiBeginFrame();
}

void Graphics::ImguiBeginFrame()
{
    if (imguiIsEnabled)
    {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
    }
}

void Graphics::ImguiRender()
{
    if (imguiIsEnabled)
    {
        ImGui::ShowDemoWindow(&show_demo_window);
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
}

void Graphics::DrawIndexed(UINT count)

{
	pContext->DrawIndexed(count, 0u, 0u);
}

void Graphics::SetMatrixProjection(DirectX::FXMMATRIX projection_in)
{
	projection = projection_in;
}

DirectX::XMMATRIX Graphics::GetMatrixProjection() const
{
	return projection;
}

void Graphics::SetImguiEnabled(bool in_b)
{
    imguiIsEnabled = in_b;
}

bool Graphics::GetImguiEnabled()
{
    return imguiIsEnabled;
}

