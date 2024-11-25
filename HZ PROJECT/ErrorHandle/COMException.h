#pragma once

#include "KotWin.h"
#include <vector>

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
	COMException(HRESULT hr, const std::string& message, std::vector<std::string> dxInfo, const std::string& file, int line)
	{
		_com_error error(hr);
		whatmsg = "msg: " + message + "\n";
		whatmsg += error.ErrorMessage();
		
		for (int i = 0; i < dxInfo.size(); i++)
		{
			whatmsg += "\n";
			whatmsg += dxInfo[i];
		}

		whatmsg += "\nfile: " + file;
		whatmsg += "\nline^ " + line;
	}
	COMException(std::vector<std::string> dxInfo, const std::string& file, int line)
	{
		
		for (int i = 0; i < dxInfo.size(); i++)
		{
			whatmsg = "\n\n";
			whatmsg += dxInfo[i];
		}

		whatmsg += "\nfile: " + file;
		whatmsg += "\nline: " + line;
	}


	std::string what()
	{
		return whatmsg;
	}
private:
	std::string whatmsg;
};


