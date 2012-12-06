/*
 * Prec.h
 *
 *  Created on: Apr 25, 2011
 *      Author: void
 */
#pragma once
#    include <AppApi.h>
#    include <irrlicht.h>
#include <limits>
#include <SharedPointer.h>

#    define INL inline
//#define INL
typedef float Real;

// These defines are for compatibility with unix msg priorities
#    ifdef WIN32
#        define LOG_EMERG   0
#        define LOG_ALERT   1
#        define LOG_CRIT    2
#        define LOG_ERR     3
#        define LOG_WARNING 4
#        define LOG_NOTICE  5
#        define LOG_INFO    6
#        define LOG_DEBUG   7
#    endif

#    ifdef DBGMODE
#        define LOG_DEBUG_MSGS 1
#    endif

#    define RENDER_D3D 1
#    define RENDER_OGL 2
#    define RENDER_OGLES1 3
#    define RENDER_OGLES2 4

#    define RENDER_PROVIDER RENDER_OGL

/////////////////////////////////////////////////////////////////////////////

enum RESOURCE_INDEX
{
    RES_UNKNOWN = 0,

    //  Model - A model represents geometry and animation data for
    //  a game entity. Entities can be props, structures or characters
    RES_MODEL,

    //Image that is applied to models using a UV map
    RES_TEXTURE,
    RES_MATERIAL,
    RES_PROGRAM,
    RES_SCRIPT,

    RES_TYPES_COUNT
} ;

enum EVENT_TYPE
{
    ON_ERROR = 0,
    ON_LOAD_COMPLETE,
} ;

enum DLGMODE
{
    OPENFILE,    SAVEFILE,    SELECTFILE
} ;

enum
{
    INDEX_NONE = -1, RESULT_NONE = -1, ROOT_INDEX = -1
} ;

enum
{
    PE_UINT_MAX = 0xFFFFFFFF,//std::numeric_limits<unsigned int>::max(),
    //PE_UINT64_MAX = 0xFFFFFFFFFFFFFFFF,
    PE_NPOS = PE_UINT_MAX
};

/// The endianness of written files
enum Endian
{
    /// Use the platform native endian
    ENDIAN_NATIVE,
    /// Use big endian (0x1000 is serialised as 0x10 0x00)
    ENDIAN_BIG,
    /// Use little endian (0x1000 is serialised as 0x00 0x10)
    ENDIAN_LITTLE
} ;

#ifndef EDITOR
extern irr::video::IVideoDriver* g_Driver;
#endif
//class CLogger;

class CSprite;
class CLevel;
class CPage;
class ILevel;
class LevelManager;
class EditablePagedLevel;
class GameObject;
class StaticGameObject;
class AnimatedGameObject;

using namespace irr;

#define MEDIA_FOLDER std::string("Media")
#define MEDIA_PATH std::string(MEDIA_FOLDER + "/")

#define ARRAY_COUNT(__arr) sizeof(__arr) / sizeof(__arr[0])

typedef video::IVideoDriver* DriverPtr;

#define USE_LOADING_FROM_XML
