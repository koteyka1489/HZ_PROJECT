#include "Drawable.h"
#include <cassert>

void Drawable::Draw(Graphics& gfx)
{
	for (auto& b : binds)
	{
		b->Bind(gfx);
	}

    for (auto& b : GetStaticBinds())
    {
        b->Bind(gfx);
    }

	gfx.DrawIndexed(GetpStaticIndexBuffer()->GetCount());
}

void Drawable::AddBind(std::unique_ptr<Bindable> bind) 
{
    // �������� �����������: ������ ��������� ��������� ����� � ������� AddBind, ��� ����� ���� AddIndexBuffer.
    // ���� ��� ������������� ������� - IndexBuffer, ������������� ������.
    assert("*Must* use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));

    // ����������� ����������� ��������� bind � ��������� binds.
    binds.push_back(std::move(bind));
}

void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> ibuf)
{
    // �������� �����������: ������ ��������� ��������� ����� ������ ������ ����.
    // ���� ��������� ����� ��� ���������� (pIndexBuffer �� ����� nullptr), ������������� ������.
    assert("Attempting to add index buffer a second time" && pIndexBuffer == nullptr);

    // ���������� ��������� �� ��������� ����� � ����� pIndexBuffer.
    pIndexBuffer = ibuf.get();

    // ����������� ����������� ��������� ibuf � ��������� binds.
    binds.push_back(std::move(ibuf));
}
