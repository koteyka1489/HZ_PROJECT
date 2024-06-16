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
	DirectX::XMMATRIX GetTransformXM() const;
	void Update(float dt);
	void Draw(Graphics& gfx);

protected:
	void AddBind(std::unique_ptr<Bindable> bind);
	void AddIndexBuffer(std::unique_ptr<IndexBuffer> bind);

private:
	virtual const std::vector < std::unique_ptr<Bindable>>& GetStaticBinds() const = 0;
	virtual const IndexBuffer* GetpStaticIndexBuffer() = 0;
protected:
	std::vector<std::unique_ptr<Bindable>> binds;
	const IndexBuffer* pIndexBuffer = nullptr;
	//pos
	float r;
	float roll = 0.f;
	float pitch = 0.f;
	float yaw = 0.f;
	float theta;
	float phi;
	float chi;

	//speed
	float droll = 0.f;
	float dpitch = 0.f;
	float dyaw = 0.f;
	float dtheta;
	float dphi;
	float dchi;

	//scale
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	float scaleZ = 1.0f;
};

