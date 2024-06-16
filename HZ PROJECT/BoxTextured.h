#pragma once
#include "DrawableBase.h"
#include <random>
#include "BindableBase.h"
#include "VertexIndexedListBox.h"

class BoxTextured : public DrawableBase<BoxTextured>
{
public:
	BoxTextured(Graphics& gfx,
		std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist,
		std::uniform_real_distribution<float>& sdist);

private:
	VertexIndexedListBox verIndListBox;
};