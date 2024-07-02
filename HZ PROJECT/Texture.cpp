#include "Texture.h"

Texture::Texture(Graphics& gfx, const std::wstring& fileName)
{
    INFOMAN(gfx);

    // Загрузка текстуры в виде поверхностных данных
    hr = DirectX::CreateWICTextureFromFile(GetDevice(gfx), GetContext(gfx), fileName.c_str(), &pResource, &pShaderResourceView, 0u);
    THROW_COM_ERROR_GFX_INFO(hr, "ERROR CreateWICTextureFromFile");

    // Получение информации о текстуре
    pResource->QueryInterface<ID3D11Texture2D>(&pTexture);
    D3D11_TEXTURE2D_DESC textureDesc;
    pTexture->GetDesc(&textureDesc);

    // Создание текстуры с поддержкой mipmapping
    textureDesc.MipLevels = 0; // Создать все мип-уровни
    textureDesc.BindFlags |= D3D11_BIND_RENDER_TARGET;

    ComPtr<ID3D11Texture2D> pTextureWithMips;
    hr = GetDevice(gfx)->CreateTexture2D(&textureDesc, nullptr, &pTextureWithMips);
    THROW_COM_ERROR_GFX_INFO(hr, "ERROR CreateTexture2D");

    // Копирование данных из загруженной текстуры в новую текстуру
    GetContext(gfx)->CopyResource(pTextureWithMips.Get(), pTexture.Get());

    // Создание Shader Resource View с мипами
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = -1;

    hr = GetDevice(gfx)->CreateShaderResourceView(pTextureWithMips.Get(), &srvDesc, &pShaderResourceView);
    THROW_COM_ERROR_GFX_INFO(hr, "ERROR CreateShaderResourceView");

    // Генерация мип-уровней
    GetContext(gfx)->GenerateMips(pShaderResourceView.Get());
}

void Texture::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->PSSetShaderResources(0u, 1u, pShaderResourceView.GetAddressOf());
}
