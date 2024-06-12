#include "Graphics.h"





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
	sd.BufferCount = 2;
	sd.OutputWindow = hWnd;
	sd.Windowed = true;
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


	// CREATE DEPTH STENCIL VIEW
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	ComPtr<ID3D11DepthStencilState> pDSState;
	hr = pDevice->CreateDepthStencilState(&dsDesc, &pDSState);
	THROW_COM_ERROR_GFX_INFO(hr, "CreateDepthStencilState");

	pContext->OMSetDepthStencilState(pDSState.Get(), 1u);

	ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = 1200u;
	descDepth.Height = 800u;
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
	THROW_COM_ERROR_GFX_INFO(hr, "reateDepthStencilView");

	// создание ViewPort
	D3D11_VIEWPORT vp;
	vp.Width = 1200.f;
	vp.Height = 800.f;
	vp.MinDepth = 0.f;
	vp.MaxDepth = 1.f;
	vp.TopLeftX = 0.f;
	vp.TopLeftY = 0.f;

	pContext->RSSetViewports(1u, &vp);

	projection = DirectX::XMMatrixPerspectiveLH(1.f, 3.f / 4.f, 0.5f, 40.f);
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
	pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::DrawTestTriangle(float angle, float x, float z)
{


	
	
	// СОЗДАНИЕ БУФЕРА ВЕРШИН 
	 // указатель на буфер верщшин
	


	// СОЗДАНИЕ БУФЕРА ИНДЕКСОВ
	const unsigned short indexes[] =
	{
		0, 2, 1,  2, 3, 1,
		1, 3, 5,  3, 7, 5,
		2, 6, 3,  3, 6, 7,
		4, 5, 7,  4, 7, 6,
		0, 4, 2,  2, 4, 6,
		0, 1, 4,  1, 5, 4
	};
	
	
	//// Создание constsnt Буфера для матрицы трансформации
	//struct ConstantBuffer
	//{
	//	dx::XMMATRIX transform;
	//};

	//ConstantBuffer cb =
	//{
	//	{
	//		dx::XMMatrixTranspose (
	//			dx::XMMatrixRotationZ(angle * 2) *
	//			dx::XMMatrixRotationX(angle) *
	//			dx::XMMatrixTranslation(x, 0, z + 5.f) *
	//			
	//			)
	//	}
	//};

	
	

	



	struct ConstantBuffer2
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		}face_colors[6];
	};

	ConstantBuffer2 cb2 =
	{
		{
			{1.0f, 1.0f, 1.0f},
			{0.0f, 0.0f, 0.0f},
			{1.0f, 0.0f, 1.0f},
			{0.0f, 1.0f, 0.0f},
			{1.0f, 1.0f, 0.0f},
			{0.0f, 1.0f, 1.0f}
		}
	};
	float xeew = cb2.face_colors[0].r;

	ComPtr<ID3D11Buffer> pConstantBuffer2;
	D3D11_BUFFER_DESC CBDesc2 = { };
	CBDesc2.ByteWidth = sizeof(cb2);
	CBDesc2.Usage = D3D11_USAGE_DEFAULT;
	CBDesc2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	CBDesc2.CPUAccessFlags = 0u;
	CBDesc2.MiscFlags = 0u;
	CBDesc2.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA ConsSubResData2 = {};
	ConsSubResData2.pSysMem = &cb2;

	hr = pDevice->CreateBuffer(&CBDesc2, &ConsSubResData2, &pConstantBuffer2);
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR pDevice->CreateBuffer Constant2");
	

	// указатель через который можно получить доступ к считанным данным
	

	

	// СОЗДАНИЕ И УСТАНОВКА PIXEL SHADER
	
	

	// СОЗДАНИЕ И УСТАНОВКА VERTEX SHADER
	

	
	

	// input layout



	// УСТАНОВКА RENDER TARGET
	pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), pDSV.Get());


	




	

}

void Graphics::DrawIndexed(UINT count)
{
	THROW_COM_ERROR_GFX_ONLY_INFO(pContext->DrawIndexed(count, 0u, 0u));
}

void Graphics::SetMatrixProjection(DirectX::FXMMATRIX projection_in)
{
	projection = projection_in;
}

DirectX::XMMATRIX Graphics::GetMatrixProjection()
{
	return projection;
}

