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
	
	WNDCLASSEX wcex = { 0 }; //  ���������, ������� �������� ���������� � ������ ����
	wcex.cbSize = sizeof(WNDCLASSEX); // ������ ���������
	wcex.style = CS_OWNDC; // ����� ������ ����, � ������ ������ ��������������� ���� CS_OWNDC, ������� ��������� ���� ����� ����������� �������� ���������� ����������� (device context).
	wcex.lpfnWndProc = HandleMsgSetup; // ��������� �� ������� WndProc, ������� ����� ������������ ��������� ����.
	wcex.cbClsExtra = 0; // ���������� �������������� ������, ���������� ��� ������ ����
	wcex.cbWndExtra = 0; // ���������� �������������� ������, ���������� ��� ������� ���������� ����
	wcex.hInstance = GetInstance(); // ���������� ���������� ����������
	wcex.hIcon = static_cast<HICON>(LoadImage(GetInstance(), MAKEINTRESOURCE( IDI_ICON3 ), IMAGE_ICON, 32, 32, 0));
	wcex.hCursor = nullptr; // ���������� ������� ��� ������ ����
	wcex.hbrBackground = nullptr; //  ���������� ����� ��� ���� ����
	wcex.lpszMenuName = nullptr; //  ��� ������ ���� ��� ������ ����
	wcex.lpszClassName = GetName(); //  ��������� �� ������ � ������ ������ ����.
	wcex.hIconSm = static_cast<HICON>(LoadImage(GetInstance(), MAKEINTRESOURCE (IDI_ICON3), IMAGE_ICON, 16, 16, 0));

	// ����������� ������ Windows
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
		0, // �������������� ����� ���� (� ������ ������ �����������)
		WindowClass::GetName(), // ��������� �� ������ � ������ ������ ����
		GetTitle(), // ��������� �� ������ � ���������� ����
		WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU, //  ����� ����, � ������ ������ ���� ����� ����� ���������, ������ ������������ � ��������� ����
		CW_USEDEFAULT, CW_USEDEFAULT, // ��������� ����� x y
		rectWin.right - rectWin.left, rectWin.bottom - rectWin.top, // ������� ���� ������ � ������
		nullptr, nullptr,
		WindowClass::GetInstance(), // ���������� ���������� ����������
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
	// ������������� ��������� ��������, ����������� �� CreateWindow(), ��� ���������� ��������� ������ ���� �� ������� WinAPI
	if (msg == WM_NCCREATE)
	{
		// ���������� ��������� �� ����� ���� �� ������ ��������
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// ��������� ����������� WinAPI ������ ������������ ��� ���������� ��������� �� ��������� ����
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// ��������� ����������� ��������� � ���������� (�� �����������) ����� ���������� ���������
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		// ��������� ��������� ����������� ���������� ����
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	// ���� �� �������� ��������� �� ��������� WM_NCCREATE, ���������� ��� � ������� ����������� �� ���������
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// ��������� ��������� �� ��������� ����
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// ��������� ��������� ����������� ���������� ����
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		// ��������� ��������� � ������
		PostQuitMessage(0);
		return 0;

	case WM_KILLFOCUS: // ��������� ��������� � ������ ������ ����
		kbd.ClearState(); 
		break;

// ��������� ��������� � ����������

	case WM_KEYDOWN: // ����� � �� ������
	case WM_SYSKEYDOWN: // ��������� ������� ������
		if (!(lParam & 0x40000000) || kbd.AutoRepeatIsEnabled())
		{
			kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;

	case WM_KEYUP: // ����� � �� �������
	case WM_SYSKEYUP: // ��������� ������� ������� 
		kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;

	case WM_CHAR:
		kbd.OnChar(static_cast<unsigned char>(wParam));
		break;

// ��������� ��������� ����
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