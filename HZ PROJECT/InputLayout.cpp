#include "InputLayout.h"

InputLayout::InputLayout(Graphics& gfx, ID3DBlob* pVertexShaderBytecode)
{
	INFOMAN(gfx);

	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	hr = GetDevice(gfx)->CreateInputLayout(ied, (UINT)std::size(ied), pVertexShaderBytecode->GetBufferPointer(), pVertexShaderBytecode->GetBufferSize(), &pInputLayout);
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR CreateInputLayout");

}

void InputLayout::Bind(Graphics& gfx)
{
	//bind input layout
	GetContext(gfx)->IASetInputLayout(pInputLayout.Get());
}
