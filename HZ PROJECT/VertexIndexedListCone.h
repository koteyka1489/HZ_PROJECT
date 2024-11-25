#pragma once
#include "VertexIndexedList.h"

class VertexIndexedListCone : public VertexIndexedList
{
public:
    VertexIndexedListCone()
    {
        const int numSegments = 16; 
        const float radius = 1.0f;
        const float height = 2.0f;
        const float angleStep = 2.0f * 3.14159265359f / numSegments;

        
        vertices.emplace_back(0.0f, height, 0.0f); 

        
        for (int i = 0; i < numSegments; ++i)
        {
            float angle = i * angleStep;
            float x = radius * cos(angle);
            float z = radius * sin(angle);
            vertices.emplace_back(x, 0.0f, z);
        }

       
        vertices.emplace_back(0.0f, 0.0f, 0.0f); 

        
        for (int i = 0; i < numSegments; ++i)
        {
            int next = (i + 1) % numSegments;
            indexes.push_back(0);        
            indexes.push_back(i + 1);    
            indexes.push_back(next + 1); 
        }

        
        for (int i = 0; i < numSegments; ++i)
        {
            int next = (i + 1) % numSegments;
            indexes.push_back(numSegments + 1); 
            indexes.push_back(next + 1);        
            indexes.push_back(i + 1);           
        }
    }
};
