#include "ErrorLogger.h"


void ErrorLogger::Log(std::string message)
{
	std::string errorMesage = "Error: " + message;
	MessageBox(nullptr, errorMesage.c_str(), "ERROR", MB_OK | MB_ICONEXCLAMATION);
}

void ErrorLogger::Log(HRESULT hr, std::string message)
{
	_com_error error(hr);
	std::string errorMesage = "Error: " + message + "\n" + error.ErrorMessage();
	MessageBox(nullptr, errorMesage.c_str(), "ERROR", MB_OK | MB_ICONEXCLAMATION);
}

void ErrorLogger::Log(COMException& exception)
{
	MessageBox(nullptr, exception.what().c_str(), "ERROR", MB_OK | MB_ICONEXCLAMATION);
}
