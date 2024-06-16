#pragma once
#include "DrawableBase.h"
#include <random>
#include "VertexIndexedListOcto.h"
#include "BindableBase.h"

class Octo : public DrawableBase<Octo>
{
public:
	Octo(Graphics& gfx,
		std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist);

private:
	VertexIndexedListOcto verIndListOcto;
};

