#include "Floor.h"

Floor::Floor(Graphics& gfx, float width, float height, float xStart, float yStart, float zStart)
{
	bool randomCoord = false;
	bool worldRot = false;
	bool modelRot = true;
	bool moving = false;
	std::wstring texfilename = L"images//grass.jpg";
	float yaw = 0.f;
	float pitch = DirectX::XM_PIDIV2;
	float roll = 0.f;

	floorShapes = std::make_unique<SheetTextured>(gfx, randomCoord, worldRot, modelRot, moving, xStart, yStart, zStart, yaw, pitch, roll, width, height, texfilename);
}

std::unique_ptr<SheetTextured>&& Floor::GetSheetTexturedWall()
{
	return std::move(floorShapes);
}
