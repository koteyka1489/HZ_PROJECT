#pragma once
#include "VertexIndexedList.h"
class VertexIndexedListPrism : public VertexIndexedList
{
public:
	VertexIndexedListPrism()
    {
        // Задание координат вершин для треугольной призмы
        vertices.emplace_back(-1.0f, -1.0f, -1.0f); // 0: Нижний левый задний угол
        vertices.emplace_back(1.0f, -1.0f, -1.0f);  // 1: Нижний правый задний угол
        vertices.emplace_back(0.0f, -1.0f, 1.0f);   // 2: Нижний центральный передний угол
        vertices.emplace_back(-1.0f, 1.0f, -1.0f);  // 3: Верхний левый задний угол
        vertices.emplace_back(1.0f, 1.0f, -1.0f);   // 4: Верхний правый задний угол
        vertices.emplace_back(0.0f, 1.0f, 1.0f);    // 5: Верхний центральный передний угол

        // Задание индексов для отрисовки граней призмы
        indexes =
        {
            // Нижняя грань
            0, 1, 2,

            // Верхняя грань
            3, 5, 4,

            // Боковые грани
            0, 2, 3,  2, 5, 3, // левая боковая грань
            2, 1, 5,  1, 4, 5, // правая боковая грань
            1, 0, 4,  0, 3, 4  // задняя боковая грань
        };
    }
};

