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

	const std::vector<Vertex> vertices = // создание масива вершин треугольника
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

	auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
	auto pvsbt = pvs->GetByteCode();
	AddBind(std::move(pvs));

	AddBind(std::make_unique<PixelShader>(gfx, L"PixelShader.cso"));

	const std::vector<unsigned short> indexes =
	{
		0, 2, 1,  2, 3, 1,
		1, 3, 5,  3, 7, 5,
		2, 6, 3,  3, 6, 7,
		4, 5, 7,  4, 7, 6,
		0, 4, 2,  2, 4, 6,
		0, 1, 4,  1, 5, 4
	};
	AddIndexBuffer(std::make_unique<IndexBuffer>(gfx, indexes));

	struct ConstantBuffer2
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		}face_colors[6];
	};

	const ConstantBuffer2 cb2 =
	{
		{
			{1.0f, 1.0f, 1.0f},
			{0.0f, 0.0f, 0.0f},
			{1.0f, 0.0f, 1.0f},
			{0.0f, 1.0f, 0.0f},
			{1.0f, 1.0f, 0.0f},
			{0.0f, 1.0f, 1.0f}
		}
	};

	AddBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2>>(gfx, cb2));

	AddBind(std::make_unique<InputLayout>(gfx, pvsbt));

	AddBind(std::make_unique<Topology>(gfx, D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));

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
