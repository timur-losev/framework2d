#pragma once

//#define ENABLE_BOOST

#include "Defs.h"
//#include "SharedPtrForward.h"
#include "AppApi.h"
#include "Types.h"
#include "Logger.h"
#include "Ptr.h"
#include "Invoker.h"

namespace Common
{
    std::wstring StringToWString(const std::string &theString);    
    std::string WStringToString(const std::wstring &theString);
}


#ifdef WIN32
typedef HWND WinHandle;
#else
typedef void* WinHandle;
#endif