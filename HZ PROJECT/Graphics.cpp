#include "Graphics.h"

#pragma comment (lib, "d3d11.lib")


Graphics::Graphics(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	);
	THROW_COM_ERROR_GFX(hr, "ERROR CREATE DEVICE");

	ID3D11Resource* pBackBuffer = nullptr;

	hr = pSwap->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	THROW_COM_ERROR_GFX(hr, "ERROR Get Buffer");

	hr = pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pTarget);
	THROW_COM_ERROR_GFX(hr, "ERROR CREATE Render Target View");

	pBackBuffer->Release();
}

Graphics::~Graphics()
{
	if (pDevice != nullptr)
	{
		pDevice->Release();
	}
	if (pSwap != nullptr)
	{
		pSwap->Release();
	}
	if (pContext != nullptr)
	{
		pContext ->Release();
	}
	if (pTarget != nullptr)
	{
		pTarget->Release();
	}
}

void Graphics::EndFrame()
{
	hr = pSwap->Present(1u, 0u);
	THROW_COM_ERROR_GFX(hr, "ERROR pSwap Present");
}

void Graphics::ClearBuffer(float red, float green, float blue)
{
	const float color[] = { red, green, blue, 1.0f };
	pContext->ClearRenderTargetView(pTarget, color);
}
