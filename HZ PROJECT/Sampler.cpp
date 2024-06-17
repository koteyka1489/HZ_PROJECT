#include "Sampler.h"

Sampler::Sampler(Graphics& gfx)
{
	INFOMAN(gfx);

	D3D11_SAMPLER_DESC sdc = {};
	sdc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sdc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sdc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sdc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sdc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sdc.MinLOD = 0;
	sdc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = GetDevice(gfx)->CreateSamplerState(&sdc, &pSamplerState);
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR CreateSamplerState");
}

void Sampler::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->PSSetSamplers(0u, 1u, pSamplerState.GetAddressOf());
}
