#pragma once
#include "KotWin.h"
#include <d3d11.h>
#include "ThrowMacros.h"
#include <wrl.h>
#include "DxgiInfoManager.h"
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <dxgidebug.h>
#include <dxgi1_3.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "D3DCompiler.lib")
#pragma comment (lib, "DXGI.lib")

#define ComPtr Microsoft::WRL::ComPtr

class Graphics
{
	friend class Bindable;
public:
	Graphics(HWND hWnd);
	~Graphics();
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	void EndFrame();
	void ClearBuffer(float red, float green, float blue);
	void DrawIndexed(UINT count);
	void SetMatrixProjection(DirectX::FXMMATRIX projection_in);
	DirectX::XMMATRIX GetMatrixProjection() const;
private:
	HRESULT hr;
	ComPtr<ID3D11Device> pDevice;
	ComPtr<ID3D11DeviceContext> pContext;
	ComPtr<IDXGISwapChain> pSwap;
	ComPtr<ID3D11RenderTargetView> pTarget;
	ComPtr<ID3D11DepthStencilView> pDSV;
	DirectX::XMMATRIX projection;
#ifndef NDEBUG
	IDXGIDebug* dxgiDebug;
	DxgiInfoManager infoManager;
#endif
	
};

