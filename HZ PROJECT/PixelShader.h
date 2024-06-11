#pragma once
#include "Bindable.h"
class PixelShader : public Bindable
{
public:
	PixelShader(Graphics& gfx, std::wstring fileName);
	void Bind(Graphics& gfx) override;
protected:
	ComPtr<ID3DBlob> pBlob;
	ComPtr<ID3D11PixelShader> pPixelShader; 
};

