#pragma once
#include "Bindable.h"
class InputLayout :  public Bindable
{
public:

	InputLayout(Graphics& gfx, ID3DBlob* pVertexShaderBytecode);
	void Bind(Graphics& gfx) override;

protected:
	ComPtr<ID3D11InputLayout> pInputLayout;
};

