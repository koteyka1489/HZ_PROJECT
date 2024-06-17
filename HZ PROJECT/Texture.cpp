#include "Texture.h"

Texture::Texture(Graphics& gfx, std::wstring fileName)
{
	INFOMAN(gfx);
	
	hr = DirectX::CreateWICTextureFromFile(GetDevice(gfx), fileName.c_str(), &pResource, &pShaderResourceView, 0u);
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR CreateWICTextureFromFile");
	
}

void Texture::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->PSSetShaderResources(0u, 1u, pShaderResourceView.GetAddressOf());
}
