#pragma once
#include "DrawableBase.h"
#include <random>
#include "VertexIndexedListSphere.h"
#include "BindableBase.h"

class Sphere : public DrawableBase<Sphere>
{
public:
	Sphere(Graphics& gfx, bool randomCoord, bool worldRot, bool modelRot, bool moving);

private:
	VertexIndexedListSphere verIndListSphere;
};

