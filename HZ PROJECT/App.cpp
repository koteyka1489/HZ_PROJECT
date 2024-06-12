#include "App.h"

App::App()
	:
	wnd(1200, 800),
	gfx(wnd.GetHwnd())
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
    std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
    std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
    std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
    for (auto i = 0; i < 5; i++)
    {
        boxes.push_back(std::make_unique<Box>(
            gfx, rng, adist,
            ddist, odist, rdist
        ));
    }
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
	auto dt = timer.Mark();
	gfx.ClearBuffer(0.07f, 0.0f, 0.12f);
	for (auto& b : boxes)
	{
		b->Update(dt);
		b->Draw(gfx);
	}
    gfx.EndFrame();
}
