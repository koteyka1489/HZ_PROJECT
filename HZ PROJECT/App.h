#pragma once
#include "Window.h"
#include "ChiliTimer.h"
#include "Box.h"
#include "Prism.h"

class App
{
public:
	App();
	int Go();

private:
	void DoFrame();

private:
	Window wnd;
	Graphics gfx;
	ChiliTimer timer;
	std::vector <std::unique_ptr<Prism>> shapes;
	static constexpr int boxesCount = 100;


};

