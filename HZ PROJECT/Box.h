#pragma once
#include "DrawableBase.h"
#include <random>
#include "BindableBase.h"
#include "VertexIndexedListBox.h"


class Box : public DrawableBase<Box>
{
public:
	Box(Graphics& gfx,
		std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist);
		

	void Update(float dt) override;
	DirectX::XMMATRIX GetTransformXM() const override;

private:
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

	VertexIndexedListBox verIndListBox;
};

