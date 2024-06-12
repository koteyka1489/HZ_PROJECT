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

		// ��������� ��� �������� ������� ������, ������� �� ���������� ����������.
		D3D11_MAPPED_SUBRESOURCE msr;

		// ����������� (map) ������, ����������� ��� �������� ������ � ��� ������.
		// D3D11_MAP_WRITE_DISCARD ������������ ��� ��������, ��� �� ����� ��������� �������������� ������.
		// hr ����� ��������� ��������� ���������� ������� Map.
		hr = GetContext(gfx)->Map(
			pConstantBuffer.Get(), // ��������� �� �����, ������� ����� ����������.
			0u, // ����� ���������� (0 ��� ����������� �������).
			D3D11_MAP_WRITE_DISCARD, // ���� ��� �������� ���� ������� � ������ (������ ����������).
			0u, // �������������� ����� (�� ������������).
			&msr // ��������� �� ���������, ������� ����� ��������� ����������� � ������������ ������� ������.
		);

		THROW_COM_ERROR_GFX_INFO(hr, "ERROR Map Constant Buffer");

		// ����������� ������ �� consts � ������������ ������� ������.
		// msr.pData ��������� �� ������ ������������ ������� ������.
		memcpy(msr.pData, &consts, sizeof(consts));

		// ��������������� (unmap) ������, ���������� ������ � ��� ������.
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
		GetContext(gfx)->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf()); //�������� ������ ��������  � pipeline � Vertex Shader
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
		GetContext(gfx)->PSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf()); //�������� ������ ��������  � pipeline � Pixel Shader
	}
};