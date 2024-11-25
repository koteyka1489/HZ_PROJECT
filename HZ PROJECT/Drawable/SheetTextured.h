#pragma once
#include "DrawableBase.h"
#include <random>
#include "BindableBase.h"

class SheetTextured : public DrawableBase<SheetTextured>
{
public:
	SheetTextured(Graphics& gfx, bool randomCoord, bool worldRot, bool modelRot, bool moving,
		float x_in, float y_in, float z_in, float yaw_in, float pitch_in, float roll_in, float scaleX_in, float scaleY_in,
		const std::wstring& texFilename);

};