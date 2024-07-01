#pragma once
#include "SheetTextured.h"

class Floor
{
public:
	Floor(Graphics& gfx, float width, float height, float xStart, float yStart, float zStart);
	std::unique_ptr<SheetTextured>&& GetSheetTexturedWall();
private:
	std::unique_ptr<SheetTextured> floorShapes;
};


