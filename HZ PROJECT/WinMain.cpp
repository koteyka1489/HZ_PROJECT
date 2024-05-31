#include "KotWin.h"
#include "Window.h"
#include "CharToWchar.h"


// Определение статических строковых переменных с использованием макроса _T для поддержки обоих ANSI и Unicode символов.


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	try
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
	}
	catch (const ChiliException& e)
	{
		CharToWchar what(e.what());
		CharToWchar type(e.GetType());
		
		MessageBox(nullptr, what.GetWchar(), type.GetWchar(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		CharToWchar what(e.what());

		MessageBox(nullptr, what.GetWchar(), L"Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, L"No details available", L"Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;

};