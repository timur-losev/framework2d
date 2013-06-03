/*
 * File:   EdPrec.h
 * Author: void
 *
 * Created on September 22, 2012, 8:33 PM
 */

#ifndef EDPREC_H
#    define	EDPREC_H

#define USE_INVOKER
#define _IRR_STATIC_LIB_

#ifdef _VARIADIC_MAX
#undef _VARIADIC_MAX
#endif
#define _VARIADIC_MAX 10

#include "Prec.h"
#include "Logger.h"
#include "DynamicMemoryStream.h"
#include "FileStream.h"
#include <tinyxml.h>

#include <Signaling.h>
#include <ThreadBase.h>
#include <functional>
#include "boost/signal.hpp"
#include "boost/bind.hpp"

#ifdef USE_INVOKER
    #include "Invoker.h"
#endif

typedef gui::IGUIFont* DebugFontPtr;

#ifdef WIN32
typedef void* MyWinId;
#elif __linux__
typedef unsigned long MyWinId;
#endif

struct RenderContext
{
    DriverPtr       Driver;
    DebugFontPtr    DebugFont;

    RenderContext():
        Driver(nullptr),
        DebugFont(nullptr)
    {}

};

enum EMouseButtons
{
    EMB_LEFT,
    EMB_MIDDLE,
    EMB_RIGHT,
    EMB_NONE
};

enum EButtonState
{
    EBS_KEY_DOWN,
    EBS_KEY_UP,
    EBS_KEY_PRESSED
};

enum EPosRelation
{
    ABSOLUTE_POS,
    RELATIVE_POS
};

class IMainWindow;
struct IRegularView;

#endif	/* EDPREC_H */

