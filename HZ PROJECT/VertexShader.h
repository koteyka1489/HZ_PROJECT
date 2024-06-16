#pragma once
#include "Bindable.h"

class VertexShader :  public Bindable
{
public:
	VertexShader(Graphics& gfx, std::wstring fileName);
	ID3DBlob* GetByteCode();
	void Bind(Graphics& gfx) noexcept override;
protected:
	ComPtr<ID3DBlob> pBlob;
	ComPtr<ID3D11VertexShader> pVertexShader; 
};

