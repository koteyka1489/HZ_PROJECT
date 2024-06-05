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
	THROW_COM_ERROR_GFX_ONLY_INFO(pContext->ClearRenderTargetView(pTarget.Get(), color));
}

void Graphics::DrawTestTriangle()
{

	struct Vertex // базовая структура вершин
	{
		struct
		{
			float x;
			float y;
		} pos;
		struct
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		} color;
		
	};

	Vertex vertices[] = // создание масива вершин треугольника
	{
		{ 0.f,   0.5f, 255, 50,  50,  0},
		{ 0.5f, -0.5f, 50,  255, 50,  0},
		{-0.5f, -0.5f, 50,  50,  255, 0},
		{-0.3f,  0.3f, 50,  255, 50,   0},
		{ 0.3f,  0.3f, 50,  50,  255, 0},
		{ 0.f,  -0.8f, 255, 50,  50,   0}
	};
	
	
	// Создание vertex buffer 
	ComPtr<ID3D11Buffer> pVertexBuffer; // указатель на буфер верщшин
	D3D11_BUFFER_DESC VBDesc = {}; // описание свойств для буфера
	VBDesc.ByteWidth = sizeof(vertices);
	VBDesc.Usage = D3D11_USAGE_DEFAULT;
	VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VBDesc.CPUAccessFlags = 0u;
	VBDesc.MiscFlags = 0u;
	VBDesc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA verSubResData = {}; // описание данных
	verSubResData.pSysMem = vertices; // указание что данные это вершины

	hr = pDevice->CreateBuffer(&VBDesc, &verSubResData, &pVertexBuffer); // создание бафера с использованием описания бафера, описание данных
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR pDevice->CreateBuffer Vertexes");

	// СОЗДАНИЕ БУФЕРА ИНДЕКСОВ
	const unsigned short indexes[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 1,
		2, 1, 5
	};
	ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC IBDesc = { };
	IBDesc.ByteWidth = sizeof(indexes);
	IBDesc.Usage = D3D11_USAGE_DEFAULT;
	IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IBDesc.CPUAccessFlags = 0u;
	IBDesc.MiscFlags = 0u;
	IBDesc.StructureByteStride = sizeof(unsigned short);

	D3D11_SUBRESOURCE_DATA indSubResData = {};
	indSubResData.pSysMem = indexes;

	hr = pDevice->CreateBuffer(&IBDesc, &indSubResData, &pIndexBuffer);
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR pDevice->CreateBuffer Indexes");



	const UINT stride = sizeof(Vertex); // шаг
	const UINT offset = 0u; // смещение

	pContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset); //связывание буфера вершин в pipeline
	pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);

	// указатель через который можно получить доступ к считанным данным
	ComPtr<ID3DBlob> pBlob; 

	// СОЗДАНИЕ И УСТАНОВКА PIXEL SHADER
	ComPtr<ID3D11PixelShader> pPixelShader; // создание указателя на Pixel Shader
	hr = D3DReadFileToBlob(L"PixelShader.cso", &pBlob); // Считывание прекомпилированного файла вершинного шейдера PixelShader.cso и загрузка его в память.
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR D3DReadFileToBlob");
	hr = pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader); // создание Pixel Shader
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR CreatePixelShader");
	pContext->PSSetShader(pPixelShader.Get(), nullptr, 0);

	// СОЗДАНИЕ И УСТАНОВКА VERTEX SHADER
	ComPtr<ID3D11VertexShader> pVertexShader; // создание указателя на шейдер вершин
	
	hr = D3DReadFileToBlob(L"VertexShader.cso", &pBlob); // Считывание прекомпилированного файла вершинного шейдера VertexShader.cso и загрузка его в память.
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR D3DReadFileToBlob");
	hr = pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader); // создание Vertex Shader
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR CreateVertexShader");
	pContext->VSSetShader(pVertexShader.Get(), nullptr, 0);

	// input layout
	ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	hr = pDevice->CreateInputLayout(ied, (UINT)std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR CreateInputLayout");
	
	//bind input layout
	pContext->IASetInputLayout(pInputLayout.Get());


	// УСТАНОВКА RENDER TARGET
	pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), nullptr);


	//set primitive Topology
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	// создание ViewPort
	D3D11_VIEWPORT vp;
	vp.Width = 1200.f;
	vp.Height = 800.f;
	vp.MinDepth = 0.f;
	vp.MaxDepth = 1.f;
	vp.TopLeftX = 0.f;
	vp.TopLeftY = 0.f;

	pContext->RSSetViewports(1u, &vp);

	THROW_COM_ERROR_GFX_ONLY_INFO(pContext->DrawIndexed((UINT)std::size(indexes), 0u, 0u));

}

