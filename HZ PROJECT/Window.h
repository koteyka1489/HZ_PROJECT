#pragma once
#include "KotWin.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <optional>
#include "Graphics.h"
#include "ThrowMacros.h"

class Window
{

private:
    class WindowClass
    {

        // Public Methods
    public:
        static const CHAR* GetName();
        static HINSTANCE GetInstance();

        // Private Methods
    private:
        WindowClass();
        ~WindowClass();
        WindowClass(const WindowClass&)            = delete;
        WindowClass& operator=(const WindowClass&) = delete;
        // Fields
    private:
        static const std::string wndClassName;
        static WindowClass wndClass;
        HINSTANCE hInstance;
    };

    // Public Methods
public:
    Window(int width, int height);
    ~Window();
    Window(const Window&)            = delete;
    Window& operator=(const Window&) = delete;
    const CHAR* GetTitle();
    void SetTitle(const std::string str);
    static std::optional<int> PrecessMessages();
    HWND GetHwnd();

    // Private Methods
private:
    static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

    // Fields
public:
    Keyboard kbd;
    Mouse mouse;

private:
    int width             = 0;
    int height            = 0;
    std::string titleName = "HZ PROJECT";
    HWND hWnd;
};
