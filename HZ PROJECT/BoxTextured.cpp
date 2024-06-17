#include "BoxTextured.h"

BoxTextured::BoxTextured(Graphics& gfx, std::mt19937& rng, std::uniform_real_distribution<float>& adist, std::uniform_real_distribution<float>& ddist, std::uniform_real_distribution<float>& odist, std::uniform_real_distribution<float>& rdist, std::uniform_real_distribution<float>& sdist)
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
	scaleZ = 1.f;
	if (IsStaticNonInitialized())
	{
		struct Vertex
		{
			struct
			{
				float x;
				float y;
				float z;
			} pos;

			struct
			{
				float u;
				float v;
			} tex;
		};

		const std::vector<Vertex> vertices =
		{
			{{-1.f, -1.f, -1.0f}, {0.0f, 1.0f}},
			{{ 1.f, -1.f, -1.0f}, {1.0f, 1.0f}},
			{{-1.f,  1.f, -1.0f}, {0.0f, 0.0f}},
			{{ 1.f,  1.f, -1.0f}, {1.0f, 0.0f}},
			{{-1.f, -1.f,  1.0f}, {0.0f, 1.0f}},
			{{ 1.f, -1.f,  1.0f}, {1.0f, 1.0f}},
			{{-1.f,  1.f,  1.0f}, {0.0f, 0.0f}},
			{{ 1.f,  1.f,  1.0f}, {1.0f, 0.0f}}
		};

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));

		AddStaticBind(std::make_unique<Texture>(gfx, L"images//head.png"));

		AddStaticBind(std::make_unique<Sampler>(gfx));

		auto pvs = std::make_unique<VertexShader>(gfx, L"TextureVertexShader.cso");
		auto pvsbt = pvs->GetByteCode();
		AddStaticBind(std::move(pvs));


		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, verIndListBox.GetIndexes()));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};

		AddStaticBind(std::make_unique<InputLayout>(gfx, pvsbt, ied));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"TexturePixelShader.cso"));

	}

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}
