#include <windows.h>
#include <tchar.h> //  �������� ������� ��� ������ � ��������� � �������� � ����������� �� �������� Unicode ��� ANSI ����������
#include <string>
#include <sstream>


// ����������� ����������� ��������� ���������� � �������������� ������� _T ��� ��������� ����� ANSI � Unicode ��������.
static TCHAR pClassName[] = _T("HZ PROJECT");
static TCHAR pTitle[] = _T("HZ");


// ��������� ���������� ��������� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	case WM_CLOSE:
	{
		PostQuitMessage(666);
		break;
	}

	case WM_KEYDOWN:
	{
		if (wParam == 'F')
		{
			SetWindowText(hWnd, _T("KURWA"));
		}
		break;
	}

	case WM_KEYUP:
	{
		if (wParam == 'F')
		{
			SetWindowText(hWnd, _T("MATKA"));
		}
		break;
	}

	case WM_CHAR:
	{
		static std::wstring nString;
		nString.push_back(wchar_t(wParam));
		SetWindowText(hWnd, nString.c_str());
		break;
	}

	case WM_LBUTTONDOWN:
	{
		POINTS pt = MAKEPOINTS(lParam);
		std::wostringstream woss;
		woss << "X - " << pt.x << " Y - " << pt.y;
		SetWindowText(hWnd, woss.str().c_str());
		break;
	}

	}

	

	return DefWindowProc(hWnd, msg, wParam, lParam); // DefWindowProc ������������ ��������� ��������� �� ���������.
}


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	// ���������� ����������  ��� ����������� ������ Windows
	WNDCLASSEX wcex = {0}; //  ���������, ������� �������� ���������� � ������ ����
	wcex.cbSize = sizeof(WNDCLASSEX); // ������ ���������
	wcex.style = CS_OWNDC; // ����� ������ ����, � ������ ������ ��������������� ���� CS_OWNDC, ������� ��������� ���� ����� ����������� �������� ���������� ����������� (device context).
	wcex.lpfnWndProc = WndProc; // ��������� �� ������� WndProc, ������� ����� ������������ ��������� ����.
	wcex.cbClsExtra = 0; // ���������� �������������� ������, ���������� ��� ������ ����
	wcex.cbWndExtra = 0; // ���������� �������������� ������, ���������� ��� ������� ���������� ����
	wcex.hInstance = hInstance; // ���������� ���������� ����������
	wcex.hIcon = nullptr; // ���������� ������ ��� ������ ����
	wcex.hCursor = nullptr; // ���������� ������� ��� ������ ����
	wcex.hbrBackground = nullptr; //  ���������� ����� ��� ���� ����
	wcex.lpszMenuName = nullptr; //  ��� ������ ���� ��� ������ ����
	wcex.lpszClassName = pClassName; //  ��������� �� ������ � ������ ������ ����.
	wcex.hIconSm = nullptr;//  ���������� ���������� ������ ��� ������ ����

	// ����������� ������ Windows
	RegisterClassEx(&wcex);

	// �������� ��������� ����
	HWND hWnd = CreateWindowEx( 
		0, // �������������� ����� ���� (� ������ ������ �����������)
		pClassName, // ��������� �� ������ � ������ ������ ����
		pTitle, // ��������� �� ������ � ���������� ����
		WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU, //  ����� ����, � ������ ������ ���� ����� ����� ���������, ������ ������������ � ��������� ����
		200, 200, // ��������� ����� x y
		1200, 800, // ������� ���� ������ � ������
		nullptr, nullptr, // ��������� �� ������������ ���� (� ������ ������ �����������)
		hInstance, // ���������� ���������� ����������
		nullptr // ��������� �� ������ ���������� ���� (� ������ ������ �����������)
	);


	// ����������� ����
	ShowWindow(hWnd, SW_SHOW);

	// ��������� ���������
	MSG msg;
	while ( GetMessage(&msg, nullptr, 0, 0) > 0 )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
};