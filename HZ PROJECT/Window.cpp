#include "Window.h"
#include "resource.h"


const std::string Window::WindowClass::wndClassName = "HZ PROJECT";
Window::WindowClass Window::WindowClass::wndClass;

const CHAR* Window::WindowClass::GetName()
{
    return wndClassName.c_str();
}

HINSTANCE Window::WindowClass::GetInstance()
{
    return wndClass.hInstance;
}

Window::WindowClass::WindowClass()
	:
	hInstance(GetModuleHandle(nullptr))
{
	
	WNDCLASSEX wcex = { 0 }; //  структура, которая содержит информацию о классе окна
	wcex.cbSize = sizeof(WNDCLASSEX); // размер структуры
	wcex.style = CS_OWNDC; // стиль класса окна, в данном случае устанавливается флаг CS_OWNDC, который позволяет окну иметь собственный контекст устройства отображения (device context).
	wcex.lpfnWndProc = HandleMsgSetup; // указатель на функцию WndProc, которая будет обработчиком сообщений окна.
	wcex.cbClsExtra = 0; // количество дополнительной памяти, выделенной для класса окна
	wcex.cbWndExtra = 0; // количество дополнительной памяти, выделенной для каждого экземпляра окна
	wcex.hInstance = GetInstance(); // дескриптор экземпляра приложения
	wcex.hIcon = static_cast<HICON>(LoadImage(GetInstance(), MAKEINTRESOURCE( IDI_ICON3 ), IMAGE_ICON, 32, 32, 0));
	wcex.hCursor = nullptr; // дескриптор курсора для класса окна
	wcex.hbrBackground = nullptr; //  дескриптор кисти для фона окна
	wcex.lpszMenuName = nullptr; //  имя строки меню для класса окна
	wcex.lpszClassName = GetName(); //  указатель на строку с именем класса окна.
	wcex.hIconSm = static_cast<HICON>(LoadImage(GetInstance(), MAKEINTRESOURCE (IDI_ICON3), IMAGE_ICON, 16, 16, 0));

	// Регистрация класса Windows
	RegisterClassEx(&wcex);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(GetName(), hInstance);
}

Window::Window(int width, int height)
	:
	width(width),
	height(height)
{
	RECT rectWin;
	rectWin.left = 100;
	rectWin.right = rectWin.left + width;
	rectWin.top = 100;
	rectWin.bottom = rectWin.top + height;

	if (AdjustWindowRect(&rectWin, WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU, false) == 0)
	{
		CHWND_LAST_EXCEPT();
	}

	hWnd = CreateWindowExA(
		0, // дополнительные стили окна (в данном случае отсутствуют)
		WindowClass::GetName(), // указатель на строку с именем класса окна
		GetTitle(), // указатель на строку с заголовком окна
		WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU, //  стили окна, в данном случае окно будет иметь заголовок, кнопку максимизации и системное меню
		CW_USEDEFAULT, CW_USEDEFAULT, // стартовая точка x y
		rectWin.right - rectWin.left, rectWin.bottom - rectWin.top, // размеры окна ширина и высота
		nullptr, nullptr,
		WindowClass::GetInstance(), // дескриптор экземпляра приложения
		this
	);

	UpdateWindow(hWnd);
	ShowWindow(hWnd, SW_SHOW);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

const CHAR* Window::GetTitle()
{
	return titleName.c_str();
}

void Window::SetTitle(const std::string str)
{
	if (SetWindowText(hWnd, str.c_str()) == 0)
	{
		throw CHWND_LAST_EXCEPT();
	}
}

LRESULT Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// использование параметра создания, переданного из CreateWindow(), для сохранения указателя класса окна на стороне WinAPI
	if (msg == WM_NCCREATE)
	{
		// извлечение указателя на класс окна из данных создания
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// установка управляемых WinAPI данных пользователя для сохранения указателя на экземпляр окна
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// установка обработчика сообщения в нормальный (не настроечный) после завершения настройки
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		// пересылка сообщения обработчику экземпляра окна
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	// если мы получили сообщение до сообщения WM_NCCREATE, обработать его с помощью обработчика по умолчанию
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// получение указателя на экземпляр окна
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// пересылка сообщения обработчику экземпляра окна
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		// обработка сообщения о выходе
		PostQuitMessage(0);
		return 0;

	case WM_KILLFOCUS: // обработка сообщения о потере фокуса окна
		kbd.ClearState(); 
		break;

// ОБРАБОТКА СООБЩЕНИЙ С КЛАВИАТУРЫ

	case WM_KEYDOWN: // буквы и тд нажаты
	case WM_SYSKEYDOWN: // системные клавиши нажаты
		if (!(lParam & 0x40000000) || kbd.AutoRepeatIsEnabled())
		{
			kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;

	case WM_KEYUP: // буквы и тд подняты
	case WM_SYSKEYUP: // ситсемные клавиши подняты 
		kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;

	case WM_CHAR:
		kbd.OnChar(static_cast<unsigned char>(wParam));
		break;

// ОБРАБОТКА СООБЩЕНИЙ МЫШИ
	case WM_MOUSEMOVE:
		POINTS pt = MAKEPOINTS(lParam);
		mouse.OnMouseMove(pt.x, pt.y);
		break;
	
	case WM_LBUTTONDOWN:
		mouse.OnLeftIsPressed();
		break;

	case WM_LBUTTONUP:
		mouse.OnLeftIsReleased();
		break;

	case WM_RBUTTONDOWN:
		mouse.OnRightIsPressed();
		break;

	case WM_RBUTTONUP:
		mouse.OnRightIsReleased();
		break;

	case WM_MOUSEWHEEL:
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
		{
			mouse.OnwheelUP();
		}
		else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
		{
			mouse.OnWheelDown();
		}

	}
	
	
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// Window Exception Stuff
Window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept
	:
	ChiliException(line, file),
	hr(hr)
{}

const char* Window::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] " << GetErrorCode() << std::endl
		<< "[Description] " << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Window::Exception::GetType() const noexcept
{
	return "Chili Window Exception";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuf = nullptr;
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
	);
	if (nMsgLen == 0)
	{
		return "Unidentified error code";
	}
	std::string errorString = pMsgBuf;
	LocalFree(pMsgBuf);
	return errorString;
}

HRESULT Window::Exception::GetErrorCode() const noexcept
{
	return hr;
}

std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}