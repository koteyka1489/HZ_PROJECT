#pragma once
#include "VertexIndexedList.h"
class VertexIndexedListPrism : public VertexIndexedList
{
public:
	VertexIndexedListPrism()
	{
        
        vertices.emplace_back(-1.0f, -1.0f, -1.0f);
        vertices.emplace_back(1.0f, -1.0f, -1.0f); 
        vertices.emplace_back(0.0f, -1.0f, 1.0f);  
        vertices.emplace_back(-1.0f, 1.0f, -1.0f); 
        vertices.emplace_back(1.0f, 1.0f, -1.0f);  
        vertices.emplace_back(0.0f, 1.0f, 1.0f);   

        
        indexes =
        {
            0, 1, 3,
            1, 4, 3,
            1, 2, 4,
            2, 5, 4,
            2, 0, 5,
            0, 3, 5,
            3, 4, 5
        };
	}
};

