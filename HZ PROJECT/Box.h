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
		std::uniform_real_distribution<float>& rdist,
		std::uniform_real_distribution<float>& sdist);

private:
	VertexIndexedListBox verIndListBox;
};

