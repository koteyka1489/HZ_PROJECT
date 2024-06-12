#pragma once
#include "Bindable.h"
#include <DirectXMath.h>
#include "IndexBuffer.h"


class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	Drawable& operator=(const Drawable&) = delete;
	virtual ~Drawable() = default;
	virtual DirectX::XMMATRIX GetTransformXM() const= 0;
	virtual void Update(float dt) = 0;

	void Draw(Graphics& gfx);
	void AddBind(std::unique_ptr<Bindable> bind);
	void AddIndexBuffer(std::unique_ptr<IndexBuffer> bind);

protected:
	std::vector<std::unique_ptr<Bindable>> binds;
	const IndexBuffer* pIndexBuffer = nullptr;
};

