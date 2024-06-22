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
	static constexpr int boxesCount = 20;
	float speedFactor = 1.0f;
	Camera camera;

};

