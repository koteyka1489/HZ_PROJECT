#include "Prism.h"

Prism::Prism(Graphics& gfx, std::mt19937& rng, std::uniform_real_distribution<float>& adist, std::uniform_real_distribution<float>& ddist, std::uniform_real_distribution<float>& odist, std::uniform_real_distribution<float>& rdist)
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
	if (IsStaticNonInitialized())
	{

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, verIndListPrism.GetVertices()));

		auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
		auto pvsbt = pvs->GetByteCode();
		AddStaticBind(std::move(pvs));


		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, verIndListPrism.GetIndexes()));

		AddStaticBind(std::make_unique<InputLayout>(gfx, pvsbt));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));



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

		AddStaticBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2>>(gfx, cb2));



		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PixelShader.cso"));

	}

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}


void Prism::Update(float dt)
{
	roll += droll * dt;
	pitch += dpitch * dt;
	yaw += dyaw * dt;
	theta += dtheta * dt;
	phi += dphi * dt;
	chi += dchi * dt;
}

DirectX::XMMATRIX Prism::GetTransformXM() const
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(r, 0.0f, 0.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 40.0f);
}
