#include "SheetTextured.h"

SheetTextured::SheetTextured(Graphics& gfx, bool randomCoord, bool worldRot, bool modelRot, bool moving, float x_in, float y_in, float z_in,float yaw_in, float pitch_in, float roll_in, const std::wstring& texFilename)
{

	isRandomCoord = randomCoord;
	isWorldCoordRotate = worldRot;
	isModelCoordRotate = modelRot;
	IsMoving = moving;
	x = x_in;
	y = y_in;
	z = z_in;
	scaleZ = 0.01f;
	scaleX = 20.f;
	scaleY = 20.f;
	yaw = yaw_in;
	pitch = pitch_in;
	roll = pitch_in;
	
	if (isRandomCoord)
	{
		RandomCoordInit();
	}

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
			// Front face
			{{-1.f, -1.f, -1.f}, {0.0f, 1.0f}},
			{{ 1.f, -1.f, -1.f}, {1.0f, 1.0f}},
			{{-1.f,  1.f, -1.f}, {0.0f, 0.0f}},
			{{ 1.f,  1.f, -1.f}, {1.0f, 0.0f}},
			// Back face
			{{-1.f, -1.f,  1.f}, {0.0f, 1.0f}},
			{{ 1.f, -1.f,  1.f}, {1.0f, 1.0f}},
			{{-1.f,  1.f,  1.f}, {0.0f, 0.0f}},
			{{ 1.f,  1.f,  1.f}, {1.0f, 0.0f}},
		};

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));

		AddStaticBind(std::make_unique<Texture>(gfx, texFilename));

		AddStaticBind(std::make_unique<Sampler>(gfx));

		auto pvs = std::make_unique<VertexShader>(gfx, L"TextureVertexShader.cso");
		auto pvsbt = pvs->GetByteCode();
		AddStaticBind(std::move(pvs));

		// Индексы для всех граней куба
		const std::vector<unsigned short> indices =
		{
			0, 2, 1, 2, 3, 1,      // Front
			4, 5, 6, 5, 7, 6,      // Back
		};

		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

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
