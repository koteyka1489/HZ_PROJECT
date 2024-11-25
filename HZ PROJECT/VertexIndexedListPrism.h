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
            0, 1, 2,
            3, 5, 4,
            0, 2, 3,  2, 5, 3, 
            2, 1, 5,  1, 4, 5, 
            1, 0, 4,  0, 3, 4  
        };
    }
};

