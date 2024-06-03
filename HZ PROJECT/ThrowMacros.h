#pragma once

#include "COMException.h"

#define THROW_COM_ERROR_LAST(msg) throw COMException(GetLastError(), msg, __FILE__, __LINE__)
#define THROW_COM_ERROR_GFX(hr, msg) if ( FAILED( hr ) ) throw COMException(hr, msg, __FILE__, __LINE__)