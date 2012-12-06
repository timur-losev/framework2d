#include "PixelFormatInternal.h"

namespace irr { namespace video {

    u32 computePitch( ECOLOR_FORMAT format, u32 width )
    {
        u32 blockSizeX = getBlockSize(format, 0);
        return (blockSizeX > 1
            // reminder: getBytesPerPixel() returns the number of bytes per
            // block instead of pixel if format is a block-aligned format
            ? (width + blockSizeX - 1) / blockSizeX * getBytesPerPixel(format)
            : getBitsPerPixel(format) * width / 8);
    }

}}
