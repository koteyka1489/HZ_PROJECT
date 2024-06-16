#include "InputLayout.h"

InputLayout::InputLayout(Graphics& gfx, ID3DBlob* pVertexShaderBytecode, const std::vector<D3D11_INPUT_ELEMENT_DESC>& ied)
{
	INFOMAN(gfx);

	

	hr = GetDevice(gfx)->CreateInputLayout(ied.data(), (UINT)ied.size(), pVertexShaderBytecode->GetBufferPointer(), pVertexShaderBytecode->GetBufferSize(), &pInputLayout);
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR CreateInputLayout");

}

void InputLayout::Bind(Graphics& gfx) noexcept
{
	//bind input layout
	GetContext(gfx)->IASetInputLayout(pInputLayout.Get());
}
