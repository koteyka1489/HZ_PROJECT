#pragma once
#include "Bindable.h"
#include <DirectXMath.h>
#include "IndexBuffer.h"
#include <random>


class Drawable
{
	template <class T>
	friend class DrawableBase;

public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	Drawable& operator=(const Drawable&) = delete;
	virtual ~Drawable() = default;
	DirectX::XMMATRIX GetMatrix() const;
	void Update(float dt);
	void Draw(Graphics& gfx);

protected:
	void AddBind(std::unique_ptr<Bindable> bind);
	void AddIndexBuffer(std::unique_ptr<IndexBuffer> bind);
	void RandomCoordInit();
private:
	virtual const std::vector < std::unique_ptr<Bindable>>& GetStaticBinds() const = 0;
	virtual const IndexBuffer* GetpStaticIndexBuffer() = 0;
	DirectX::XMMATRIX GetTransformXMRotateAll() const;
	DirectX::XMMATRIX GetTransformXMRotateModelCoord() const;
	DirectX::XMMATRIX GetTransformXMRotateWorldCoord() const;
	DirectX::XMMATRIX GetTransformXMTranslate() const;
	
protected:
	std::vector<std::unique_ptr<Bindable>> binds;
	const IndexBuffer* pIndexBuffer = nullptr;
	//pos
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float roll = 0.f;
	float pitch = 0.f;
	float yaw = 0.f;
	float theta = 0.f;
	float phi = 0.f;
	float chi = 0.f;

	//speed
	float droll = 0.5f;
	float dpitch = 0.5f;
	float dyaw = 0.5f;
	float dtheta = 0.5f;
	float dphi = 0.5f;
	float dchi = 0.5f;

	//scale
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	float scaleZ = 1.0f;

	bool isModelCoordRotate = false;
	bool isWorldCoordRotate = false;
	bool isRandomCoord = false;
	bool IsMoving = false;
};

