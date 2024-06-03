#include "KotWin.h"
#include "App.h"
#include "ErrorLogger.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	try
	{
		App app;
		return app.Go();
	}

	catch (COMException& exception)
	{
		ErrorLogger::Log(exception);
	}

	catch (...)
	{
		ErrorLogger::Log("Unkown Exception");
	}

	return -1;
};