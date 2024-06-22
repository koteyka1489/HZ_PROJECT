#pragma once
#include "DrawableBase.h"
#include <random>
#include "VertexIndexedListOcto.h"
#include "BindableBase.h"

class Octo : public DrawableBase<Octo>
{
public:
	Octo(Graphics& gfx, bool randomCoord, bool worldRot, bool modelRot, bool moving);

private:
	VertexIndexedListOcto verIndListOcto;
};

