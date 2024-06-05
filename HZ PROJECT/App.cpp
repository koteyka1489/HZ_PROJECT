#include "App.h"

App::App()
	:
	wnd(1200, 800),
	gfx(wnd.GetHwnd())
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
    const float dt = ft.MarkRealDt() * 50.0f; 
    if (red < 250.f)
    {
        red += dt;
        green += dt;
        blue -= dt;
    }
    else
    {
        red = 0.f;
        green = 0.f;
        blue = 250.f;
    }
    gfx.ClearBuffer(red / 255.f, green / 255.f, blue / 255.f);
    gfx.DrawTestTriangle();
    gfx.EndFrame();
}
