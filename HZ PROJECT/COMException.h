#pragma once

#include "KotWin.h"

class COMException
{
public:
	COMException(HRESULT hr, const std::string& message, const std::string& file, int line)
	{
		_com_error error(hr);
		whatmsg = "msg: " + message + "\n";
		whatmsg += error.ErrorMessage();
		whatmsg += "\nfile: " + file;
		whatmsg += "\nline^ " + line;
	}
	std::string what()
	{
		return whatmsg;
	}
private:
	std::string whatmsg;
};


