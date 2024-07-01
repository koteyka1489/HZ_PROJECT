#pragma once
#include "Window.h"
#include "ChiliTimer.h"
#include "Box.h"
#include "Prism.h"
#include "Cone.h"
#include "Octo.h"
#include "BoxTextured.h"
#include "imgui\ImguiManager.h"
#include "Camera.h"
#include "SheetTextured.h"
#include "Wall.h"
#include "Floor.h"
#include "Sphere.h"

class App
{
public:
	App();
	int Go();

private:
	void DoFrame();

private:
	ImguiManager imgui;
	Window wnd;
	Graphics gfx;
	ChiliTimer timer;
	std::vector <std::unique_ptr<Drawable>> shapes;
	static constexpr int boxesCount = 1;
	float speedFactor = 1.0f;
	Camera camera;
	Wall leftWall;
	Wall rightWall;
	Wall frontWall;
	Floor floor;
};

