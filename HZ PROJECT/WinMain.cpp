#include <windows.h>
#include <tchar.h>

static TCHAR pClassName[] = _T("HZ PROJECT");
static TCHAR pTitle[] = _T("HZ");

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	
	WNDCLASSEX wcex = {0};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = DefWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = nullptr;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = pClassName;
	wcex.hIconSm = nullptr;


	RegisterClassEx(&wcex);


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

	ShowWindow(hWnd, SW_SHOW);
	while (true);

	return 0;
};