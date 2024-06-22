#include "TransformCBuff.h"

std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> TransformCbuf::vcbuf = nullptr;

TransformCbuf::TransformCbuf(Graphics& gfx, const Drawable& parent)
	:
	parent(parent)
{
	if (!vcbuf)
	{
		vcbuf = std::make_unique<VertexConstantBuffer<DirectX::XMMATRIX>>(gfx);
	}
}

void TransformCbuf::Bind(Graphics& gfx) noexcept
{
	vcbuf->Update(gfx,
		DirectX::XMMatrixTranspose(
			parent.GetTransformXMTranslate() *
			gfx.GetMatrixCamera() *
			gfx.GetMatrixProjection()
		)
	);
	vcbuf->Bind(gfx);
}
