#pragma once
#include "SheetTextured.h"

class Wall
{
public:
	Wall(Graphics& gfx, float width, float height, float xStart, float yStart, float zStart, float yaw_in);
	std::unique_ptr<SheetTextured>&& GetSheetTexturedWall();
private:
	std::unique_ptr<SheetTextured> wallShapes;
};

