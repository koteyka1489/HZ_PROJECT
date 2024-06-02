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
	FrameTimer ft;
	float dt = 0.f;
};

