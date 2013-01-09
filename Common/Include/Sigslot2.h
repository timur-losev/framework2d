#pragma once

#ifdef _MSC_VER
    #ifdef _VARIADIC_MAX
    #undef _VARIADIC_MAX
    #endif
    #define _VARIADIC_MAX 10

    #include "SigSlot2_variadic_support_msvc.h"
#else
#include "SigSlot2_variadic_support_full.h"
//#include "Sigslot2_adaptive_gcc.h"
#endif