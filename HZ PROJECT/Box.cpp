#include "Box.h"

Box::Box(Graphics& gfx, std::mt19937& rng, std::uniform_real_distribution<float>& adist, std::uniform_real_distribution<float>& ddist, std::uniform_real_distribution<float>& odist, std::uniform_real_distribution<float>& rdist)
	:
	r(rdist(rng)),
	droll(ddist(rng)),
	dpitch(ddist(rng)),
	dyaw(ddist(rng)),
	dphi(odist(rng)),
	dtheta(odist(rng)),
	dchi(odist(rng)),
	chi(adist(rng)),
	theta(adist(rng)),
	phi(adist(rng))
{
	struct Vertex // базовая структура вершин
	{
		struct
		{
			float x;
			float y;
			float z;
		} pos;
	};

	std::vector<Vertex> vertices = // создание масива вершин треугольника
	{
		{-1.f, -1.f, -1.0f},
		{ 1.f, -1.f, -1.0f},
		{-1.f,  1.f, -1.0f},
		{ 1.f,  1.f, -1.0f},
		{-1.f, -1.f,  1.0f},
		{ 1.f, -1.f,  1.0f},
		{-1.f,  1.f,  1.0f},
		{ 1.f,  1.f,  1.0f}
	};

	AddBind(std::make_unique<VertexBuffer>(gfx, vertices));



}

void Box::Update(float dt)
{
	roll += droll * dt;
	pitch += dpitch * dt;
	yaw += dyaw * dt;
	theta += dtheta * dt;
	phi += dphi * dt;
	chi += dchi * dt;
}

DirectX::XMMATRIX Box::GetTransformXM() const
{

	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) * 
		DirectX::XMMatrixTranslation(r, 0.f, 0.f) *
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
		DirectX::XMMatrixTranslation(0.f, 0.f, 20.f);
}
