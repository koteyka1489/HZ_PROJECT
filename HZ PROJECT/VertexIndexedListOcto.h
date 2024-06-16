#pragma once
#include "VertexIndexedList.h"

class VertexIndexedListOcto : public VertexIndexedList
{
public:
	VertexIndexedListOcto()
	{
        vertices =
        {
            { 1.0f,  0.0f,  0.0f},  // 0
            {-1.0f,  0.0f,  0.0f},  // 1
            { 0.0f,  1.0f,  0.0f},  // 2
            { 0.0f, -1.0f,  0.0f},  // 3
            { 0.0f,  0.0f,  1.0f},  // 4
            { 0.0f,  0.0f, -1.0f}   // 5
        };

        // Индексы октаэдра
        indexes =
        {
            // Верхние четыре треугольника
            0, 2, 4,
            2, 1, 4,
            1, 3, 4,
            3, 0, 4,

            // Нижние четыре треугольника
            0, 5, 2,
            2, 5, 1,
            1, 5, 3,
            3, 5, 0
        };

	}
};