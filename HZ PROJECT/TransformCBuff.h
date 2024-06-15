#pragma once
#include "Bindable.h"
#include "ConstantBuffer.h"
#include "Drawable.h"

class TransformCbuf : public Bindable
{
public:
	TransformCbuf(Graphics& gfx, const Drawable& parent);
	void Bind(Graphics& gfx) noexcept override;
private:
	static std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> vcbuf;
	const Drawable& parent;
};
