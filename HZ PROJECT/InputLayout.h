#pragma once
#include "Bindable.h"
class InputLayout :  public Bindable
{
public:

	InputLayout(Graphics& gfx, ID3DBlob* pVertexShaderBytecode, const std::vector<D3D11_INPUT_ELEMENT_DESC>& ied);
	void Bind(Graphics& gfx) noexcept override;

protected:
	ComPtr<ID3D11InputLayout> pInputLayout;
};

