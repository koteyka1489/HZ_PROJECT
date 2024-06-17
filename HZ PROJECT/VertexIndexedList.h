#pragma once
#include <vector>
#include <DirectXMath.h>

class VertexIndexedList
{
public:
	VertexIndexedList() = default;
	VertexIndexedList(const VertexIndexedList&) = delete;
	VertexIndexedList& operator=(const VertexIndexedList&) = delete;
	VertexIndexedList(const VertexIndexedList&&) = delete;
	VertexIndexedList& operator=(const VertexIndexedList&&) = delete;
	virtual ~VertexIndexedList() = default;


	std::vector<DirectX::XMFLOAT3>& GetVertices()
	{
		return vertices;
	}
	std::vector<unsigned short>& GetIndexes()
	{
		return indexes;
	}
protected:
	std::vector<DirectX::XMFLOAT3> vertices;
	std::vector<unsigned short> indexes;
	
};