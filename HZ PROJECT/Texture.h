#pragma once
#include "Bindable.h"
#include <WICTextureLoader.h>

class Texture : public Bindable
{
public:
	Texture(Graphics& gfx, const std::wstring& fileName);
	void Bind(Graphics& gfx) noexcept override;

protected:
	ComPtr<ID3D11Resource> pResource;
	ComPtr<ID3D11ShaderResourceView> pShaderResourceView;
	ComPtr<ID3D11Texture2D> pTexture;
};

