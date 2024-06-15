#include "Box.h"

Box::Box(Graphics& gfx, std::mt19937& rng, std::uniform_real_distribution<float>& adist, std::uniform_real_distribution<float>& ddist, std::uniform_real_distribution<float>& odist, std::uniform_real_distribution<float>& rdist)

{
	r = (rdist(rng));
	droll = (ddist(rng));
	dpitch = (ddist(rng));
	dyaw = (ddist(rng));
	dphi = (odist(rng));
	dtheta = (odist(rng));
	dchi = (odist(rng));
	chi = (adist(rng));
	theta = (adist(rng));
	phi = (adist(rng));
	if (IsStaticNonInitialized())
	{

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, verIndListBox.GetVertices()));

		auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
		auto pvsbt = pvs->GetByteCode();
		AddStaticBind(std::move(pvs));


		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, verIndListBox.GetIndexes()));

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


