#include "Floor.h"

Floor::Floor(Graphics& gfx, float xStart, float yStart, float zStart)
{
	bool randomCoord = false;
	bool worldRot = false;
	bool modelRot = true;
	bool moving = false;
	std::wstring texfilename = L"images//grass.jpg";
	float yaw = 0.f;
	float pitch = DirectX::XM_PIDIV2;
	float roll = 0.f;

	int nSheetsHeight = floorHeight / sheetHeight;
	int nSheetsWidth = floorWidth / sheetWidth;
	
	for (int z = 0; z < nSheetsHeight; z++)
	{
		for (int x = 0; x < nSheetsWidth; x++)
		{
			float z_temp = zStart + z * (float)sheetHeight;
			float x_temp = xStart + x * (float)sheetWidth;

			floorShapes.push_back(std::make_unique<SheetTextured>(gfx, randomCoord, worldRot, modelRot, moving, x_temp, yStart, z_temp, yaw, pitch, roll, (float)sheetWidth, (float)sheetHeight, texfilename));
		}
	}
	

}

std::vector<std::unique_ptr<SheetTextured>>&& Floor::GetSheetTexturedWall()
{
	return std::move(floorShapes);
}
