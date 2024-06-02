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
	dt += ft.MarkRealDt();
	std::ostringstream oss;
	oss << "Time - " << dt;
	wnd.SetTitle(oss.str());
}
