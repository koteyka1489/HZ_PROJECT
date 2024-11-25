#include "Drawable.h"
#include <cassert>

DirectX::XMMATRIX Drawable::GetTransformXMRotateAll() const
{
    
    return DirectX::XMMatrixScaling(scaleX, scaleY, scaleZ) *
        DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
        DirectX::XMMatrixTranslation(x, y, z) *
        DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi);
}

DirectX::XMMATRIX Drawable::GetTransformXMRotateModelCoord() const
{
    return DirectX::XMMatrixScaling(scaleX, scaleY, scaleZ) *
        DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
        DirectX::XMMatrixTranslation(x, y, z);
}

DirectX::XMMATRIX Drawable::GetTransformXMRotateWorldCoord() const
{
    return DirectX::XMMatrixScaling(scaleX, scaleY, scaleZ) *
        DirectX::XMMatrixTranslation(x, y, z) *
        DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi);;
}

DirectX::XMMATRIX Drawable::GetTransformXMTranslate() const
{
    return DirectX::XMMatrixScaling(scaleX, scaleY, scaleZ) * DirectX::XMMatrixTranslation(x, y, z);
}

void Drawable::RandomCoordInit()
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
    std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
    std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
    std::uniform_real_distribution<float> rdist(6.0f, 100.0f);
    std::uniform_real_distribution<float> sdist(0.1f, 5.0f);

    x = rdist(rng);
    droll = ddist(rng);
    dpitch = ddist(rng);
    dyaw = ddist(rng);
    dphi = odist(rng);
    dtheta = odist(rng);
    dchi = odist(rng);
    chi = adist(rng);
    theta = adist(rng);
    phi = adist(rng);

}

DirectX::XMMATRIX Drawable::GetMatrix() const
{
    if (isModelCoordRotate && isWorldCoordRotate)
    {
        return GetTransformXMRotateAll();
    }
    else if (isWorldCoordRotate)
    {
        return GetTransformXMRotateWorldCoord();
    }
    else if (isModelCoordRotate)
    {
        return GetTransformXMRotateModelCoord();
    }
    else
    {
        return GetTransformXMTranslate();
    }

}

void Drawable::Update(float dt)
{
    if (IsMoving)
    {
        roll += droll * dt;
        pitch += dpitch * dt;
        yaw += dyaw * dt;
        theta += dtheta * dt;
        phi += dphi * dt;
        chi += dchi * dt;
    }
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
   
    assert("*Must* use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));

    
    binds.push_back(std::move(bind));
}

void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> ibuf)
{
    assert("Attempting to add index buffer a second time" && pIndexBuffer == nullptr);
    
    pIndexBuffer = ibuf.get();
    
    binds.push_back(std::move(ibuf));
}
