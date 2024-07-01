#pragma once
#include "VertexIndexedList.h"

class VertexIndexedListSphere : public VertexIndexedList
{
public:
    VertexIndexedListSphere(unsigned int latitudeCount, unsigned int longitudeCount)
    {
        const float radius = 1.0f;
        const float PI = 3.14159265359f;
        const float latitudeStep = PI / latitudeCount;
        const float longitudeStep = 2.0f * PI / longitudeCount;

        // Генерация вершин
        for (unsigned int i = 0; i <= latitudeCount; ++i)
        {
            const float theta = i * latitudeStep;
            const float sinTheta = sinf(theta);
            const float cosTheta = cosf(theta);

            for (unsigned int j = 0; j <= longitudeCount; ++j)
            {
                const float phi = j * longitudeStep;
                const float sinPhi = sinf(phi);
                const float cosPhi = cosf(phi);

                float x = cosPhi * sinTheta;
                float y = cosTheta;
                float z = sinPhi * sinTheta;

                vertices.push_back({ x * radius, y * radius, z * radius });
            }
        }

        // Генерация индексов
        for (unsigned int i = 0; i < latitudeCount; ++i)
        {
            for (unsigned int j = 0; j < longitudeCount; ++j)
            {
                unsigned int first = (i * (longitudeCount + 1)) + j;
                unsigned int second = first + longitudeCount + 1;

                indexes.push_back(first);
                indexes.push_back(second);
                indexes.push_back(first + 1);

                indexes.push_back(second);
                indexes.push_back(second + 1);
                indexes.push_back(first + 1);
            }
        }
    }
};