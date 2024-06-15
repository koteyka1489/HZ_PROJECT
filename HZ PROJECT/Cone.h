#pragma once
#include "DrawableBase.h"
#include <random>
#include "VertexIndexedListCone.h"
#include "BindableBase.h"

class Cone : public DrawableBase<Cone>
{
public:
	Cone(Graphics& gfx,
		std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist);

private:
	VertexIndexedListCone verIndListCone;
};