#include "VertexBuffer.h"

void VertexBuffer::Bind(Graphics& gfx)
{
	const UINT offset = 0u; // смещение
	GetContext(gfx)->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset); //привязка буфера вершин в pipeline
}
