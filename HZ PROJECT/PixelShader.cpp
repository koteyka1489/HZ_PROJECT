#include "PixelShader.h"

PixelShader::PixelShader(Graphics& gfx, std::wstring fileName)
{
	INFOMAN(gfx);

	hr = D3DReadFileToBlob(fileName.c_str(), &pBlob); // —читывание прекомпилированного файла вершинного шейдера PixelShader.cso и загрузка его в пам€ть.
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR D3DReadFileToBlob");

	hr = GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader); // создание Pixel Shader
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR CreatePixelShader");
	
}

void PixelShader::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0);
}
