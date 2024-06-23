#include "Wall.h"

Wall::Wall(Graphics& gfx, float width, float height, float xStart, float yStart, float zStart, float yaw_in)
{
	bool randomCoord = false;
	bool worldRot = false;
	bool modelRot = true;
	bool moving = false;
	std::wstring texfilename = L"images//wall.jpg";
	float yaw = yaw_in;
	float pitch = 0.f;
	float roll = 0;

	wallShapes = std::make_unique<SheetTextured>(gfx, randomCoord, worldRot, modelRot, moving, xStart, yStart, zStart, yaw, pitch,  roll, width, height, texfilename);
}

std::unique_ptr<SheetTextured>&& Wall::GetSheetTexturedWall()
{
	return std::move(wallShapes);
}
