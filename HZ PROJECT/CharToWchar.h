#pragma once

#include <string>
#include <sstream>

class CharToWchar
{
public:
	CharToWchar(const char* char_in);
	~CharToWchar();
	wchar_t* GetWchar();
	CharToWchar(const CharToWchar&) = delete;
	CharToWchar& operator=(const CharToWchar&) = delete;
private:
	wchar_t* nStr;
};

