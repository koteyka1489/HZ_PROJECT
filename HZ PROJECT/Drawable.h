#pragma once
#include "Bindable.h"
#include <DirectXMath.h>
#include "IndexBuffer.h"


class Drawable
{
	template <class T>
	friend class DrawableBase;

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

private:
	virtual const std::vector < std::unique_ptr<Bindable>>& GetStaticBinds() const = 0;
	virtual const IndexBuffer* GetpStaticIndexBuffer() = 0;
protected:
	std::vector<std::unique_ptr<Bindable>> binds;
	const IndexBuffer* pIndexBuffer = nullptr;
};

