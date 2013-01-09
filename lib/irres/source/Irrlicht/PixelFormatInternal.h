#ifndef PixelFormatInternal_h__
#define PixelFormatInternal_h__

#include "PixelFormat.h"

namespace irr { namespace video {

inline u32 getBlockSize(ECOLOR_FORMAT format, u8 dimension)
{
    _IRR_DEBUG_BREAK(dimension < 3);
    return u32(PFDTable[format].BlockSize[dimension]);
}

inline u32 getBytesPerPixel(ECOLOR_FORMAT format)
{
    return PFDTable[format].ByteCount;
}

inline u32 getBitsPerPixel(ECOLOR_FORMAT format)
{
    return PFDTable[format].BitsPerPixel;
}

u32 computePitch(ECOLOR_FORMAT format, u32 width);

}}

#endif // PixelFormatInternal_h__
