#include "Window.h"


const std::wstring Window::WindowClass::wndClassName = L"HZ PROJECT";
Window::WindowClass Window::WindowClass::wndClass;

const WCHAR* Window::WindowClass::GetName()
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
	wcex.hIcon = nullptr; // ���������� ������ ��� ������ ����
	wcex.hCursor = nullptr; // ���������� ������� ��� ������ ����
	wcex.hbrBackground = nullptr; //  ���������� ����� ��� ���� ����
	wcex.lpszMenuName = nullptr; //  ��� ������ ���� ��� ������ ����
	wcex.lpszClassName = GetName(); //  ��������� �� ������ � ������ ������ ����.
	wcex.hIconSm = nullptr;//  ���������� ���������� ������ ��� ������ ����

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

	AdjustWindowRect(&rectWin, WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU, false);

	hWnd = CreateWindowEx(
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

const WCHAR* Window::GetTitle()
{
	return titleName.c_str();
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
		// ������� ��������� � ������
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}