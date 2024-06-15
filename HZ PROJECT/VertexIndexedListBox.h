#pragma once
#include "VertexIndexedList.h"
class VertexIndexedListBox : public VertexIndexedList
{
public:
	VertexIndexedListBox()
	{
		vertices.emplace_back(-1.0f, -1.0f, -1.0f);
		vertices.emplace_back(1.0f, -1.0f, -1.0f);
		vertices.emplace_back(-1.0f, 1.0f, -1.0f);
		vertices.emplace_back(1.0f, 1.0f, -1.0f);
		vertices.emplace_back(-1.0f, -1.0f, 1.0f);
		vertices.emplace_back(1.0f, -1.0f, 1.0f);
		vertices.emplace_back(-1.0f, 1.0f, 1.0f);
		vertices.emplace_back(1.0f, 1.0f, 1.0f);

		indexes =
		{
			0, 2, 1,  2, 3, 1,
			1, 3, 5,  3, 7, 5,
			2, 6, 3,  3, 6, 7,
			4, 5, 7,  4, 7, 6,
			0, 4, 2,  2, 4, 6,
			0, 1, 4,  1, 5, 4
		};
	}
};

