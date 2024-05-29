#include "KotWin.h"



// ����������� ����������� ��������� ���������� � �������������� ������� _T ��� ��������� ����� ANSI � Unicode ��������.

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
	
	// ��������� ���������
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
};