#include "Sphere.h"

Sphere::Sphere(Graphics& gfx, bool randomCoord, bool worldRot, bool modelRot, bool moving)
	:
	verIndListSphere(12u, 12u)
{
	isRandomCoord = randomCoord;
	isWorldCoordRotate = worldRot;
	isModelCoordRotate = modelRot;
	IsMoving = moving;

	if (isRandomCoord)
	{
		RandomCoordInit();
	}

	if (IsStaticNonInitialized())
	{

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, verIndListSphere.GetVertices()));

		auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
		auto pvsbt = pvs->GetByteCode();
		AddStaticBind(std::move(pvs));


		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, verIndListSphere.GetIndexes()));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};


		AddStaticBind(std::make_unique<InputLayout>(gfx, pvsbt, ied));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));



		struct ConstantBuffer2
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			}face_colors[1];
		};

		const ConstantBuffer2 cb2 =
		{
			{
				{1.0f, 1.0f, 1.0f}
			}
		};

		AddStaticBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2>>(gfx, cb2));



		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PixelShaderSphere.cso"));

	}

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}
