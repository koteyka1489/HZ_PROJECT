#include "CharToWchar.h"

CharToWchar::CharToWchar(const char* char_in)
{
	const char* ch = char_in;
	size_t len = std::strlen(ch) + 1;
	nStr = new wchar_t[len];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, nStr, len, ch, _TRUNCATE);
}

CharToWchar::~CharToWchar()
{
	delete[] nStr;
}

wchar_t* CharToWchar::GetWchar()
{
	return nStr;
}
