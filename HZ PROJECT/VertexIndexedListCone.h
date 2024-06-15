#pragma once
#include "VertexIndexedList.h"

class VertexIndexedListCone : public VertexIndexedList
{
public:
    VertexIndexedListCone()
    {
        const int numSegments = 16; // Количество сегментов для основания
        const float radius = 1.0f;
        const float height = 2.0f;
        const float angleStep = 2.0f * 3.14159265359f / numSegments;

        // Вершина верхушки конуса
        vertices.emplace_back(0.0f, height, 0.0f); // 0: Верхушка

        // Вершины основания конуса
        for (int i = 0; i < numSegments; ++i)
        {
            float angle = i * angleStep;
            float x = radius * cos(angle);
            float z = radius * sin(angle);
            vertices.emplace_back(x, 0.0f, z);
        }

        // Центр основания (для треугольников основания)
        vertices.emplace_back(0.0f, 0.0f, 0.0f); // numSegments + 1: Центр основания

        // Индексы для боковой поверхности
        for (int i = 0; i < numSegments; ++i)
        {
            int next = (i + 1) % numSegments;
            indexes.push_back(0);        // Верхушка
            indexes.push_back(i + 1);    // Текущая вершина основания
            indexes.push_back(next + 1); // Следующая вершина основания
        }

        // Индексы для основания
        for (int i = 0; i < numSegments; ++i)
        {
            int next = (i + 1) % numSegments;
            indexes.push_back(numSegments + 1); // Центр основания
            indexes.push_back(next + 1);        // Следующая вершина основания
            indexes.push_back(i + 1);           // Текущая вершина основания
        }
    }
};
