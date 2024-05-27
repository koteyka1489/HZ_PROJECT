#include <windows.h>
#include <tchar.h> //  содержит макросы для работы с символами и строками в зависимости от настроек Unicode или ANSI приложения


// Определение статических строковых переменных с использованием макроса _T для поддержки обоих ANSI и Unicode символов.
static TCHAR pClassName[] = _T("HZ PROJECT");
static TCHAR pTitle[] = _T("HZ");


// кастомная функция обработки сообщений
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(666);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam); // DefWindowProc обрабатывает остальные сообщения по умолчанию.
}


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	// Заполнение параметров  для регистрации класса Windows
	WNDCLASSEX wcex = {0};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = nullptr;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = pClassName;
	wcex.hIconSm = nullptr;

	// Регистрация класса Windows
	RegisterClassEx(&wcex);

	// создание экземляра окна
	HWND hWnd = CreateWindowEx(
		0,
		pClassName,
		pTitle,
		WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU,
		200, 200,
		1200, 800,
		nullptr, nullptr,
		hInstance,
		nullptr
	);


	// отображение окна
	ShowWindow(hWnd, SW_SHOW);

	// Обработка сообщений
	MSG msg;
	while ( GetMessage(&msg, nullptr, 0, 0) > 0 )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
};