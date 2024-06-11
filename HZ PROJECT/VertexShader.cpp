#include "VertexShader.h"

VertexShader::VertexShader(Graphics& gfx, std::wstring fileName)
{
	INFOMAN(gfx);
	hr = D3DReadFileToBlob(fileName.c_str(), &pBlob); // ���������� ������������������� ����� ���������� �������  � �������� ��� � ������.
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR D3DReadFileToBlob");

	hr = GetDevice(gfx)->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader); // �������� Vertex Shader
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR CreateVertexShader");
}

ID3DBlob* VertexShader::GetByteCode()
{
	return pBlob.Get();
}

void VertexShader::Bind(Graphics& gfx)
{
	GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0);
}
