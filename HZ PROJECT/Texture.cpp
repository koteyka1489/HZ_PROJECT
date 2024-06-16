#include "Texture.h"

Texture::Texture(Graphics& gfx, std::wstring fileName)
{
	INFOMAN(gfx);
	
	hr = DirectX::CreateWICTextureFromFile(GetDevice(gfx), fileName.c_str(), pResource.GetAddressOf(), pShaderResourceView.GetAddressOf(), 0u);
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR CreateWICTextureFromFile");
}

void Texture::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->PSGetShaderResources(0u, 1u, pShaderResourceView.GetAddressOf());
}
