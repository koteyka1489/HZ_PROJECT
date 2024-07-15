#include "App.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_dx11.h"
#include "imgui\imgui_impl_win32.h"

App::App()
	:
	wnd(1500, 1000),
	gfx(wnd.GetHwnd()),
	leftWall(gfx, 500.f, 200.f, -500.f, -5.f, 200.f, DirectX::XM_PIDIV2),
	rightWall(gfx, 500.f, 200.f, 500.f, -5.f, 200.f, DirectX::XM_PIDIV2),
	frontWall(gfx, 500.f, 200.f, 0.f, -5.f, 700.f, 0.f),
	floor(gfx, -2500.f, -205.f, -2500.f)
	
{
	shapes.push_back(leftWall.GetSheetTexturedWall());
	shapes.push_back(rightWall.GetSheetTexturedWall());
	shapes.push_back(frontWall.GetSheetTexturedWall());
	shapes.push_back(std::make_unique<SheetTextured>(gfx, false, false, true, false, 0.f, 50.f, 680.f, 0,
		0.f, 0.f, 100.f, 100.f, L"images//pashok.png"));
	shapes.push_back(std::make_unique<SheetTextured>(gfx, false, false, true, false, -250.f, 50.f, 680.f, 0,
		0.f, 0.f, 100.f, 100.f, L"images//kim.jpeg"));
	shapes.push_back(std::make_unique<SheetTextured>(gfx, false, false, true, false, 250.f, 50.f, 680.f, 0,
		0.f, 0.f, 100.f, 100.f, L"images//putin.jpg"));
	shapes.push_back(std::make_unique<Sphere>(gfx, false, false, true, false, 0.f, 500.f, 350.f, 50.f));
	

	auto floorShapes = floor.GetSheetTexturedWall();
	for (auto& shapeFl : floorShapes)
	{
		shapes.push_back(std::move(shapeFl));
	}

	shapes.push_back(std::make_unique<Model>(gfx, false, false, true, false, 0.f, 50.f, 200.f, 0.f, 0.f, 0.f, 100.f, 100.f, 100.f, "models//nanosuit.obj"));
 //   for (int i = 0; i < boxesCount; i++)
 //   {
	//	

	///*	if (i % 2 == 0)
	//	{
	//		shapes.push_back(std::make_unique<BoxTextured>(gfx, randomCoord, worldRot, modelRot, moving));
	//	}
	//	else if (i % 3 == 0)
	//	{
	//		shapes.push_back(std::make_unique<Cone>(gfx, randomCoord, worldRot, modelRot, moving));
	//	}
	//	else
	//	{
	//		shapes.push_back(std::make_unique<Box>(gfx, randomCoord, worldRot, modelRot, moving));
	//	}
	//	*/
	//	
 //   }
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
