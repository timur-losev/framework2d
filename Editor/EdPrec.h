/*
 * File:   EdPrec.h
 * Author: void
 *
 * Created on February 3, 2012, 10:39 PM
 */

#ifndef EDPREC_H
#    define	EDPREC_H

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include "Prec.h"
#include "boost/shared_ptr.hpp"

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

//typedef boost::shared_ptr<video::IVideoDriver> DriverPtr;
typedef video::IVideoDriver* DriverPtr;

typedef gui::IGUIFont* DebugFontPtr;

//global struct
struct G
{
    static std::stack<DriverPtr> DriverStack;
    static std::stack<DebugFontPtr> FontStack;
};

#define GVideoDriver G::DriverStack.top()
#define GDebugFont G::FontStack.top()

#ifdef __WXGTK__
        #define USE_WX_GL 0
#endif

enum EMouseButtons
{
    EMB_LEFT,
    EMB_MIDDLE,
    EMB_RIGHT,
	EMB_NONE
};

class MappingToolLevel;
class AtlasToolLevel;

#endif	/* EDPREC_H */

