#pragma once
#include "KotWin.h"
#include <d3d11.h>
#include "ThrowMacros.h"
#include <wrl.h>
#include "DxgiInfoManager.h"

#define ComPtr Microsoft::WRL::ComPtr

class Graphics
{
public:
	Graphics(HWND hWnd);
	~Graphics() = default;
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	void EndFrame();
	void ClearBuffer(float red, float green, float blue);
	void DrawTestTriangle(float angle, float x, float y);
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
};

