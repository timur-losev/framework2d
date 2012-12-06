#ifndef TextureEnums_h__
#define TextureEnums_h__

#include "irrTypes.h"

namespace irr { namespace video {

//! Type of texture
enum E_TEXTURE_TYPE
{
    //! 1D texture.
    ETT_1D,

    //! 2D texture.
    ETT_2D,

    //! 3D texture.
    ETT_3D,

    //! Cube map texture.
    ETT_CUBE_MAP,

    //! Texture rectangle.
    ETT_RECT,

    //! Texture Shadow 2D (3DS)
    ETT_SHADOW_2D,

    //! Texture Shadow Cube (3DS)
    ETT_SHADOW_CUBE,

    //! Texture projection (3DS)
    ETT_PROJECTION,

    ETT_COUNT,

    ETT_UNKNOWN = u8(-1)
};

enum E_TEXTURE_LAYOUT
{
    //! Linear format
    ETL_LINEAR,

    //!
    ETL_LINEAR_UNIFORM_PITCH,

    //! Block format 32x32
    ETL_TILED_32,

    //! 
    ETL_SWIZZLED,

    //! Used for PSP2's native RAW format (GXT)
    ETL_PSP2_RAW,

    ETL_COUNT,
    ETL_UNKNOWN = u8(-1)
};

}}

#endif // TextureEnums_h__
