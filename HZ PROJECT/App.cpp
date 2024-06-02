#include "App.h"

App::App()
	:
	wnd(1200, 800)
{
}

int App::Go()
{

	// Обработка сообщений
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		DoFrame();
	}

	return static_cast<int>(msg.wParam);
}

void App::DoFrame()
{

}
