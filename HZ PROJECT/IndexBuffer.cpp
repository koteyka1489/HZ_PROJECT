#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Graphics& gfx, const std::vector<unsigned short>& indexes)
	:
	count((UINT)indexes.size())
{
	INFOMAN(gfx);

	D3D11_BUFFER_DESC IBDesc = { };
	IBDesc.ByteWidth = UINT(count * sizeof(unsigned short));
	IBDesc.Usage = D3D11_USAGE_DEFAULT;
	IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IBDesc.CPUAccessFlags = 0u;
	IBDesc.MiscFlags = 0u;
	IBDesc.StructureByteStride = sizeof(unsigned short);

	D3D11_SUBRESOURCE_DATA indSubResData = {};
	indSubResData.pSysMem = indexes.data();

	hr = GetDevice(gfx)->CreateBuffer(&IBDesc, &indSubResData, &pIndexBuffer);
	THROW_COM_ERROR_GFX_INFO(hr, "ERROR pDevice->CreateBuffer Indexes");

}

void IndexBuffer::Bind(Graphics& gfx)
{
	GetContext(gfx)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u); //привязка буфера индексов в pipeline
}

UINT IndexBuffer::GetCount() const
{
	return count;
}
