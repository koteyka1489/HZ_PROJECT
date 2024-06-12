#pragma once
#include "Bindable.h"

template <typename C>
class ConstantBuffer : public Bindable
{
public:
	ConstantBuffer(Graphics& gfx, const C& consts)
	{
		INFOMAN(gfx);
		D3D11_BUFFER_DESC CBDesc = { };
		CBDesc.ByteWidth = sizeof(consts);
		CBDesc.Usage = D3D11_USAGE_DYNAMIC;
		CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		CBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		CBDesc.MiscFlags = 0u;
		CBDesc.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA ConsSubResData = {};
		ConsSubResData.pSysMem = &consts;

		hr = GetDevice(gfx)->CreateBuffer(&CBDesc, &ConsSubResData, &pConstantBuffer);
		THROW_COM_ERROR_GFX_INFO(hr, "ERROR pDevice->CreateBuffer Constant");
	}

	ConstantBuffer(Graphics& gfx)
	{
		INFOMAN(gfx);
		D3D11_BUFFER_DESC CBDesc = { };
		CBDesc.ByteWidth = sizeof(consts);
		CBDesc.Usage = D3D11_USAGE_DYNAMIC;
		CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		CBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		CBDesc.MiscFlags = 0u;
		CBDesc.StructureByteStride = 0u;


		hr = GetDevice(gfx)->CreateBuffer(&CBDesc, nullptr, &pConstantBuffer);
		THROW_COM_ERROR_GFX_INFO(hr, "ERROR pDevice->CreateBuffer Constant nullptr");
	}

	void Update(Graphics& gfx, const C& consts)
	{
		
		INFOMAN(gfx);

		// —труктура дл€ описани€ области пам€ти, которую мы собираемс€ отобразить.
		D3D11_MAPPED_SUBRESOURCE msr;

		// ќтображение (map) буфера, позвол€ющее нам получить доступ к его пам€ти.
		// D3D11_MAP_WRITE_DISCARD используетс€ дл€ указани€, что мы будем полностью перезаписывать данные.
		// hr будет содержать результат выполнени€ функции Map.
		hr = GetContext(gfx)->Map(
			pConstantBuffer.Get(), // ”казатель на буфер, который нужно отобразить.
			0u, // Ќомер подресурса (0 дл€ большинства случаев).
			D3D11_MAP_WRITE_DISCARD, // ‘лаг дл€ указани€ типа доступа к пам€ти (полна€ перезапись).
			0u, // ƒополнительные флаги (не используютс€).
			&msr // ”казатель на структуру, котора€ будет заполнена информацией о отображенной области пам€ти.
		);

		THROW_COM_ERROR_GFX_INFO(hr, "ERROR Map Constant Buffer");

		//  опирование данных из consts в отображенную область пам€ти.
		// msr.pData указывает на начало отображенной области пам€ти.
		memcpy(msr.pData, &consts, sizeof(consts));

		// –азмонтирование (unmap) буфера, освобожда€ доступ к его пам€ти.
		GetContext(gfx)->Unmap(pConstantBuffer.Get(), 0u);
	}

private:
	ComPtr<ID3D11Buffer> pConstantBuffer;
};


template <typename C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer::pConstantBuffer;
	using ConstantBuffer::GetContext;

public:
	using ConstantBuffer::ConstantBuffer;
	void Bind(Graphics& gfx) override
	{
		GetContext(gfx)->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf()); //прив€зка буфера констант  в pipeline к Vertex Shader
	}
};

template <typename C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer::pConstantBuffer;
	using ConstantBuffer::GetContext;

public:
	using ConstantBuffer::ConstantBuffer;
	void Bind(Graphics& gfx) override
	{
		GetContext(gfx)->PSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf()); //прив€зка буфера констант  в pipeline к Pixel Shader
	}
};