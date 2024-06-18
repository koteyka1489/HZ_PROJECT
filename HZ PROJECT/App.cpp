#include "App.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_dx11.h"
#include "imgui\imgui_impl_win32.h"

App::App()
	:
	wnd(1200, 800),
	gfx(wnd.GetHwnd())
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
    std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
    std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
    std::uniform_real_distribution<float> rdist(6.0f, 40.0f);
	std::uniform_real_distribution<float> sdist(0.1f, 5.0f);
    for (int i = 0; i < boxesCount; i++)
    {
		if (i % 2 == 0)
		{
			shapes.push_back(std::make_unique<BoxTextured>(
				gfx, rng, adist,
				ddist, odist, rdist, sdist
			));
		}
		else if (i % 3 == 0)
		{
			shapes.push_back(std::make_unique<Cone>(
				gfx, rng, adist,
				ddist, odist, rdist
			));
		}
		else
		{
			shapes.push_back(std::make_unique<Box>(
				gfx, rng, adist,
				ddist, odist, rdist, sdist
			));
		}
		
		
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
	for (auto& b : shapes)
	{
		b->Update(dt);
		b->Draw(gfx);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	static bool show_demo_window = true;
	ImGui::ShowDemoWindow(&show_demo_window);
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    gfx.EndFrame();
}
