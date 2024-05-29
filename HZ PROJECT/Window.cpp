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
	hInstance = GetModuleHandle(nullptr); // ��������� �����������


	WNDCLASSEX wcex = { 0 }; //  ���������, ������� �������� ���������� � ������ ����
	wcex.cbSize = sizeof(WNDCLASSEX); // ������ ���������
	wcex.style = CS_OWNDC; // ����� ������ ����, � ������ ������ ��������������� ���� CS_OWNDC, ������� ��������� ���� ����� ����������� �������� ���������� ����������� (device context).
	wcex.lpfnWndProc = WndProc; // ��������� �� ������� WndProc, ������� ����� ������������ ��������� ����.
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
{
	RECT rectWin;
	rectWin.left = 100;
	rectWin.right = rectWin.left + width;
	rectWin.top = 100;
	rectWin.bottom = rectWin.top + height;

	AdjustWindowRect(&rectWin, WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU, false);

	HWND hWnd = CreateWindowEx(
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
