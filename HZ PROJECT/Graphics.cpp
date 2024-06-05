#include "Graphics.h"
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "D3DCompiler.lib")

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

}


void Graphics::EndFrame()
{
#ifndef NDEBUG
	infoManager.Set();
#endif
	hr = pSwap->Present(1u, 0u);
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR pSwap Present");
}

void Graphics::ClearBuffer(float red, float green, float blue)
{
	const float color[] = { red, green, blue, 1.0f };
	pContext->ClearRenderTargetView(pTarget.Get(), color);
}

void Graphics::DrawTestTriangle()
{

	struct Vertex // ������� ��������� ������
	{
		float x;
		float y;
	};

	const Vertex vertices[] = // ��������� ������ ������ ������������
	{
		{0.f, 0.5f},
		{0.5f, -0.5f},
		{-0.5f, -0.5f}
	};
	
	// �������� vertex buffer � ���������� � render pipeline 
	ComPtr<ID3D11Buffer> pVertexBuffer; // ��������� �� ����� �������
	D3D11_BUFFER_DESC bufferDesc = {}; // �������� ������� ��� ������
	bufferDesc.ByteWidth = sizeof(vertices);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0u;
	bufferDesc.MiscFlags = 0u;
	bufferDesc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA subResData = {}; // �������� ������
	subResData.pSysMem = vertices; // �������� ��� ������ ��� �������

	hr = pDevice->CreateBuffer(&bufferDesc, &subResData, &pVertexBuffer); // �������� ������ � �������������� �������� ������, �������� ������
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR pDevice->CreateBuffer");

	const UINT stride = sizeof(Vertex); // ���
	const UINT offset = 0u; // ��������
	pContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset); //���������� ������ ������ � pipeline


	// ��������� ����� ������� ����� �������� ������ � ��������� ������
	ComPtr<ID3DBlob> pBlob; 

	// �������� � ��������� PIXEL SHADER
	ComPtr<ID3D11PixelShader> pPixelShader; // �������� ��������� �� Pixel Shader
	hr = D3DReadFileToBlob(L"PixelShader.cso", &pBlob); // ���������� ������������������� ����� ���������� ������� PixelShader.cso � �������� ��� � ������.
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR D3DReadFileToBlob");
	hr = pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader); // �������� Pixel Shader
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR CreatePixelShader");
	pContext->PSSetShader(pPixelShader.Get(), nullptr, 0);

	// �������� � ��������� VERTEX SHADER
	ComPtr<ID3D11VertexShader> pVertexShader; // �������� ��������� �� ������ ������
	
	hr = D3DReadFileToBlob(L"VertexShader.cso", &pBlob); // ���������� ������������������� ����� ���������� ������� VertexShader.cso � �������� ��� � ������.
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR D3DReadFileToBlob");
	hr = pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader); // �������� Vertex Shader
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR CreateVertexShader");
	pContext->VSSetShader(pVertexShader.Get(), nullptr, 0);

	// input layout
	ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	hr = pDevice->CreateInputLayout(ied, (UINT)std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR CreateInputLayout");
	
	//bind input layout
	pContext->IASetInputLayout(pInputLayout.Get());


	// ��������� RENDER TARGET
	pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), nullptr);


	//set primitive Topology
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	// �������� ViewPort
	D3D11_VIEWPORT vp;
	vp.Width = 1200.f;
	vp.Height = 800.f;
	vp.MinDepth = 0.f;
	vp.MaxDepth = 1.f;
	vp.TopLeftX = 0.f;
	vp.TopLeftY = 0.f;
	pContext->RSSetViewports(1u, &vp);

	THROW_COM_ERROR_GFX_ONLY_INFO(pContext->Draw((UINT)std::size(vertices), 0u));

}

