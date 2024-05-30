#include "KotWin.h"
#include "Window.h"


// Определение статических строковых переменных с использованием макроса _T для поддержки обоих ANSI и Unicode символов.


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	Window win(1200, 800);
	
	// Обработка сообщений
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
};