#include "App.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_dx11.h"
#include "imgui\imgui_impl_win32.h"

App::App()
	:
	wnd(1200, 800),
	gfx(wnd.GetHwnd())
{
	bool randomCoord = true;
	bool modelRot = true;
	bool worldRot = true;
	bool moving = true;


    for (int i = 0; i < boxesCount; i++)
    {
		//shapes.push_back(std::make_unique<BoxTextured>(gfx, true, false, false, true));

		if (i % 2 == 0)
		{
			shapes.push_back(std::make_unique<BoxTextured>(gfx, randomCoord, worldRot, modelRot, moving));
		}
		else if (i % 3 == 0)
		{
			shapes.push_back(std::make_unique<Cone>(gfx, randomCoord, worldRot, modelRot, moving));
		}
		else
		{
			shapes.push_back(std::make_unique<Box>(gfx, randomCoord, worldRot, modelRot, moving));
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
	const auto dt = timer.Mark() * speedFactor;
	gfx.BeginFrame(0.07f, 0.0f, 0.12f);
	for (auto& b : shapes)
	{
		b->Update(dt);
		b->Draw(gfx);
	}

	gfx.SetMatrixCamera(camera.GetMatrix());
	camera.SpawnControlButton();
	camera.Control(wnd, dt);

	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		speedFactor = 0.f;
	}
	else
	{
		speedFactor = 1.f;
	}

	if (ImGui::Begin("Simulation Speed"))
	{
		ImGui::SliderFloat("Speed Factor", &speedFactor, 0.0f, 4.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000 / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
	ImGui::End();


	
    gfx.EndFrame();
}
