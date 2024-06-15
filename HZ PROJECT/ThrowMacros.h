#pragma once

#include "COMException.h"

#define THROW_COM_ERROR_LAST(msg) throw COMException(GetLastError(), msg, __FILE__, __LINE__)
#define THROW_COM_ERROR_NOINFO(hr, msg) if (FAILED(hr)) throw COMException(hr, msg, __FILE__, __LINE__)

#ifndef NDEBUG
#define THROW_COM_ERROR_GFX_INFO(hr, msg) if ( FAILED( hr ) ) throw COMException(hr, msg, infoManager.GetMessages(), __FILE__, __LINE__)
#define THROW_COM_ERROR_GFX_ONLY_INFO(call) infoManager.Set(); (call); {auto v = infoManager.GetMessages(); if(!v.empty()) { throw COMException(v, __FILE__, __LINE__);}}
#else
#define THROW_COM_ERROR_GFX_INFO(hr, msg) if ( FAILED( hr ) ) throw COMException(hr, msg, __FILE__, __LINE__)
#define THROW_COM_ERROR_GFX_ONLY_INFO()
#endif

#define INFOMAN(gfx) HRESULT hr; DxgiInfoManager& infoManager = GetInfoManager((gfx))
