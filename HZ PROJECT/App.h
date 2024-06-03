#pragma once
#include "Window.h"
#include "FrameTimer.h"


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
	FrameTimer ft;
	float red = 0.f;
	float green = 0.f;
	float blue = 250.f;
};

