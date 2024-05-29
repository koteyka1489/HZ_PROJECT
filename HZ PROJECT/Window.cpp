#include "Window.h"

const WCHAR* Window::WindowClass::GetName()
{
    return wndClassName.c_str();
}

HINSTANCE Window::WindowClass::GetInstance()
{
    return hInstance;
}

Window::WindowClass::WindowClass()
{
	wndClassName = L"HZ PROJECT";
	hInstance = GetModuleHandle(nullptr); // получение дискриптора


	WNDCLASSEX wcex = { 0 }; //  структура, котора€ содержит информацию о классе окна
	wcex.cbSize = sizeof(WNDCLASSEX); // размер структуры
	wcex.style = CS_OWNDC; // стиль класса окна, в данном случае устанавливаетс€ флаг CS_OWNDC, который позвол€ет окну иметь собственный контекст устройства отображени€ (device context).
	wcex.lpfnWndProc = WndProc; // указатель на функцию WndProc, котора€ будет обработчиком сообщений окна.
	wcex.cbClsExtra = 0; // количество дополнительной пам€ти, выделенной дл€ класса окна
	wcex.cbWndExtra = 0; // количество дополнительной пам€ти, выделенной дл€ каждого экземпл€ра окна
	wcex.hInstance = GetInstance(); // дескриптор экземпл€ра приложени€
	wcex.hIcon = nullptr; // дескриптор значка дл€ класса окна
	wcex.hCursor = nullptr; // дескриптор курсора дл€ класса окна
	wcex.hbrBackground = nullptr; //  дескриптор кисти дл€ фона окна
	wcex.lpszMenuName = nullptr; //  им€ строки меню дл€ класса окна
	wcex.lpszClassName = GetName(); //  указатель на строку с именем класса окна.
	wcex.hIconSm = nullptr;//  дескриптор маленького значка дл€ класса окна

	// –егистраци€ класса Windows
	RegisterClassEx(&wcex);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(GetName(), hInstance);
}

Window::Window(int width, int height)
{
	RECT rectWin;
	rectWin.left = 100;
	rectWin.right = rectWin.left + width;
	rectWin.top = 100;
	rectWin.bottom = rectWin.top + height;

	AdjustWindowRect(&rectWin, WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU, false);

	HWND hWnd = CreateWindowEx(
		0, // дополнительные стили окна (в данном случае отсутствуют)
		WindowClass::GetName(), // указатель на строку с именем класса окна
		GetTitle(), // указатель на строку с заголовком окна
		WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU, //  стили окна, в данном случае окно будет иметь заголовок, кнопку максимизации и системное меню
		CW_USEDEFAULT, CW_USEDEFAULT, // стартова€ точка x y
		rectWin.right - rectWin.left, rectWin.bottom - rectWin.top, // размеры окна ширина и высота
		nullptr, nullptr, 
		WindowClass::GetInstance(), // дескриптор экземпл€ра приложени€
		this
	);

	ShowWindow(hWnd, SW_SHOW);

}

Window::~Window()
{
	DestroyWindow(hWnd);
}

const WCHAR* Window::GetTitle()
{
	return titleName.c_str();
}
