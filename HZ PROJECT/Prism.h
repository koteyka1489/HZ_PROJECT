#pragma once
#include "DrawableBase.h"
#include <random>
#include "VertexIndexedListPrism.h"
#include "BindableBase.h"

class Prism : public DrawableBase<Prism>
{
public:
	Prism(Graphics& gfx, bool randomCoord, bool worldRot, bool modelRot, bool moving);

private:
	VertexIndexedListPrism verIndListPrism;
};