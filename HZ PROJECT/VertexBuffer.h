#pragma once
#include "Bindable.h"

class VertexBuffer : public Bindable
{
public:
	template <typename V>
	VertexBuffer(Graphics& gfx, const std::vector<V> vertices)
		:
		stride(UINT(sizeof(V)))
	{
		INFOMAN(gfx);

		D3D11_BUFFER_DESC VBDesc = {}; // описание свойств для Vertex Buffer
		VBDesc.ByteWidth = UINT(vertices.size() * sizeof(V));
		VBDesc.Usage = D3D11_USAGE_DEFAULT;
		VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		VBDesc.CPUAccessFlags = 0u;
		VBDesc.MiscFlags = 0u;
		VBDesc.StructureByteStride = sizeof(V);

		D3D11_SUBRESOURCE_DATA verSubResData = {}; // описание данных
		verSubResData.pSysMem = &vertices; // указание что данные это вершины

		hr = GetDevice(gfx)->CreateBuffer(&VBDesc, &verSubResData, &pVertexBuffer); // создание бафера с использованием описания бафера, описание данных
		THROW_COM_ERROR_GFX_INFO(hr, "ERROR pDevice->CreateBuffer Vertexes");

	};
	void Bind(Graphics& gfx) override;
	
protected:
	UINT stride;
	ComPtr<ID3D11Buffer> pVertexBuffer;
};
