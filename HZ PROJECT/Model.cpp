#include "Model.h"

Model::Model(Graphics& gfx, bool randomCoord, bool worldRot, bool modelRot, bool moving, float x_in, float y_in, float z_in,
	float yaw_in, float pitch_in, float roll_in, float scaleX_in, float scaleY_in, float scaleZ_in, std::string fileName)
	:
	mesh(fileName)
{
	isRandomCoord = randomCoord;
	isWorldCoordRotate = worldRot;
	isModelCoordRotate = modelRot;
	IsMoving = moving;
	x = x_in;
	y = y_in;
	z = z_in;
	pitch = pitch_in;
	yaw = yaw_in;
	roll = roll_in;
	scaleX = scaleX_in;
	scaleY = scaleY_in;
	scaleZ = scaleZ_in;

	if (isRandomCoord)
	{
		RandomCoordInit();
	}

	if (IsStaticNonInitialized())
	{
		

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, mesh.GetVerTexNormCoord()));

		//AddStaticBind(std::make_unique<Texture>(gfx, L"images//pashok.png"));

		//AddStaticBind(std::make_unique<Sampler>(gfx));

		auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShaderModel.cso");
		auto pvsbt = pvs->GetByteCode();
		AddStaticBind(std::move(pvs));



		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, mesh.GetIndices()));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		AddStaticBind(std::make_unique<InputLayout>(gfx, pvsbt, ied));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PixelShaderModel.cso"));
	}

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}
