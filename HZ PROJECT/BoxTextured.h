#pragma once
#include "DrawableBase.h"
#include <random>
#include "BindableBase.h"
#include "VertexIndexedListBox.h"

class BoxTextured : public DrawableBase<BoxTextured>
{
public:
	BoxTextured(Graphics& gfx, bool randomCoord, bool worldRot, bool modelRot, bool moving);

private:
	VertexIndexedListBox verIndListBox;
};