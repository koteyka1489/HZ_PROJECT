#pragma once
#include "KotWin.h"
#include <d3d11.h>
#include "ThrowMacros.h"
#include <wrl.h>
#include "DxgiInfoManager.h"
#include <DirectXMath.h>

#define ComPtr Microsoft::WRL::ComPtr

class Graphics
{
	friend class Bindable;
public:
	Graphics(HWND hWnd);
	~Graphics() = default;
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	void EndFrame();
	void ClearBuffer(float red, float green, float blue);
	void DrawTestTriangle(float angle, float x, float y);
	void DrawIndexed(UINT count);
	void SetMatrixProjection(DirectX::FXMMATRIX projection_in);
	DirectX::XMMATRIX GetMatrixProjection();
private:

#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif
	HRESULT hr;
	ComPtr<ID3D11Device> pDevice;
	ComPtr<IDXGISwapChain> pSwap;
	ComPtr<ID3D11DeviceContext> pContext;
	ComPtr<ID3D11RenderTargetView> pTarget;
	ComPtr<ID3D11DepthStencilView> pDSV;
	DirectX::XMMATRIX projection;
	
};

