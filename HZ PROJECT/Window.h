#pragma once
#include "KotWin.h"

class Window
{
private:
	class WindowClass
	{
	// Public Methods
	public:
		static const WCHAR* GetName();
		static HINSTANCE GetInstance();

	// Private Methods
	private:
		WindowClass();
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator= (const WindowClass&) = delete;
	// Fields
	private:
		static std::wstring wndClassName;
		static HINSTANCE hInstance;
		static WindowClass wndClass;
	};

// Public Methods
public:
	Window(int width, int height);
	~Window();
	Window(const Window&) = delete;
	Window& operator= (const Window&) = delete;
	const WCHAR* GetTitle();

// Private Methods
private:

// Fields
private:
	int width;
	int height;
	std::wstring titleName = L"HZ PROJECT";
	HWND hWnd;
};

