#pragma once
#include "DrawableBase.h"
#include <random>
#include "VertexIndexedListSphere.h"
#include "BindableBase.h"

class Sphere : public DrawableBase<Sphere>
{
public:
	Sphere(Graphics& gfx, bool randomCoord, bool worldRot, bool modelRot, bool moving, float x_in, float y_in, float z_in, float scale);

private:
	VertexIndexedListSphere verIndListSphere;
};

