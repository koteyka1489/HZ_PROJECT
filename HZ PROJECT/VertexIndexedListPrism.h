#pragma once
#include "VertexIndexedList.h"
class VertexIndexedListPrism : public VertexIndexedList
{
public:
	VertexIndexedListPrism()
    {
        // ������� ��������� ������ ��� ����������� ������
        vertices.emplace_back(-1.0f, -1.0f, -1.0f); // 0: ������ ����� ������ ����
        vertices.emplace_back(1.0f, -1.0f, -1.0f);  // 1: ������ ������ ������ ����
        vertices.emplace_back(0.0f, -1.0f, 1.0f);   // 2: ������ ����������� �������� ����
        vertices.emplace_back(-1.0f, 1.0f, -1.0f);  // 3: ������� ����� ������ ����
        vertices.emplace_back(1.0f, 1.0f, -1.0f);   // 4: ������� ������ ������ ����
        vertices.emplace_back(0.0f, 1.0f, 1.0f);    // 5: ������� ����������� �������� ����

        // ������� �������� ��� ��������� ������ ������
        indexes =
        {
            // ������ �����
            0, 1, 2,

            // ������� �����
            3, 5, 4,

            // ������� �����
            0, 2, 3,  2, 5, 3, // ����� ������� �����
            2, 1, 5,  1, 4, 5, // ������ ������� �����
            1, 0, 4,  0, 3, 4  // ������ ������� �����
        };
    }
};

