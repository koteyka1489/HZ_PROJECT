#pragma once
#include "KotWin.h"
#include "COMException.h"


class ErrorLogger
{
public:
	static void Log(std::string message);
	static void Log(HRESULT HR, std::string message);
	static void Log(COMException& exception);
};

