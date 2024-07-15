#pragma once
#include "DrawableBase.h"
#include <random>
#include "BindableBase.h"
#include "Mesh.h"

class Model : public DrawableBase<Model>
{
public:
	Model(Graphics& gfx, bool randomCoord, bool worldRot, bool modelRot, bool moving, float x_in, float y_in, float z_in,
		float yaw_in, float pitch_in, float roll_in, float scaleX_in, float scaleY_in, float scaleZ_in, std::string fileName);

private:
	Mesh mesh;
};