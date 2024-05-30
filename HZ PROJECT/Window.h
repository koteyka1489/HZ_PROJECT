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
		
		static const std::wstring wndClassName;
		static WindowClass wndClass;
		HINSTANCE hInstance;
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
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

// Fields
private:
	int width = 0;
	int height = 0;
	std::wstring titleName = L"HZ PROJECT";
	HWND hWnd;
};
