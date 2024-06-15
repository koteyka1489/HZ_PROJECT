#pragma once
#include "DrawableBase.h"
#include <random>
#include "VertexIndexedListPrism.h"
#include "BindableBase.h"

class Prism : public DrawableBase<Prism>
{
public:
	Prism(Graphics& gfx,
		std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist);

private:
	VertexIndexedListPrism verIndListPrism;
};