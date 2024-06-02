#include "App.h"

App::App()
	:
	wnd(1200, 800)
{
}

int App::Go()
{
	while (true)
	{
		if (const auto ecode = Window::PrecessMessages())
		{
			return *ecode;
		}
		DoFrame();
	}
	
}

void App::DoFrame()
{
	if (dt < 250)
	{
		red = +dt;
		green += dt;
		blue -= dt;
		dt += ft.MarkRealDt();
	}
	else
	{
		dt = 0.f;
	}

	wnd.gfx().ClearBuffer(red, green, blue);
	wnd.gfx().EndFrame();
}
