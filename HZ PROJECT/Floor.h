#pragma once
#include "SheetTextured.h"

class Floor
{
public:
	Floor(Graphics& gfx, float xStart, float yStart, float zStart);
	std::vector<std::unique_ptr<SheetTextured>>&& GetSheetTexturedWall();
private:
	std::vector<std::unique_ptr<SheetTextured>> floorShapes;
	static constexpr int sheetWidth = 500;
	static constexpr int sheetHeight = 500;
	static constexpr int floorWidth = 5000;
	static constexpr int floorHeight = 5000;
};


