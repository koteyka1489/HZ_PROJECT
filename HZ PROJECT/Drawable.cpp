#include "Drawable.h"
#include <cassert>

DirectX::XMMATRIX Drawable::GetTransformXM() const
{
    
    return DirectX::XMMatrixScaling(scaleX, scaleY, scaleZ) *
        DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
        DirectX::XMMatrixTranslation(r, 0.0f, 0.0f) *
        DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
        DirectX::XMMatrixTranslation(0.0f, 0.0f, 40.0f);
}

void Drawable::Update(float dt)
{
    roll += droll * dt;
    pitch += dpitch * dt;
    yaw += dyaw * dt;
    theta += dtheta * dt;
    phi += dphi * dt;
    chi += dchi * dt;
}

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
