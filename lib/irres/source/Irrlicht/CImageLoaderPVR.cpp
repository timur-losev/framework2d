#include "CImageLoaderPVR.h"
#include "SPVRHeader.h"
#include "coreutil.h"
#include "CImage.h"
#include "CReadFile.h"
#include "os.h"
#include "irrMath.h"

#include "ITexture.h"
#include <sstream>
#include <iostream>

//#include <auto_ptr.h>

using namespace irr;
using namespace video;

bool readPVRHeader( io::IReadFile* file, detail::SPVRHeader& header );
bool processPVRHeader(io::IReadFile* file, const detail::SPVRHeader& header, STextureDesc& desc);

#define irrLog(__msg__, __loglevel__)\
    std::ostringstream ss;\
    ss<<__msg__;\
    irr::os::Printer::log(ss.str().c_str(), __loglevel__)



//#define irrLog(__msg__, __loglevel__)

//////////////////////////////////////////////////////////////////////////

bool irr::video::CImageLoaderPVR::isALoadableFileExtension( const io::path& filename ) const
{
    return core::hasFileExtension(filename, "pvr");
}

bool irr::video::CImageLoaderPVR::isALoadableFileFormat( io::IReadFile* file ) const
{
    if (file)
    {
        detail::SPVRHeader header;
        long bytesRead = file->read(&header, sizeof(detail::SPVRHeader));
        if(bytesRead == sizeof(detail::SPVRHeader)
            && header.HeaderLength == sizeof(detail::SPVRHeader)
            && strncmp(header.PVRTag, "PVR!", 4) == 0)
        {
            return true;
        }
    }

    return false;
}

IImage* irr::video::CImageLoaderPVR::loadImage( io::IReadFile* file ) const
{
    detail::SPVRHeader header;
    if(!readPVRHeader(file, header))
    {
        return NULL;
    }

    //TODO: maybe boost::shared_array ?
    u8* data = new u8 [header.DataLength];

    long bytesRead = file->read(data, header.DataLength);
    
    if(bytesRead != long(header.DataLength))
    {
        os::Printer::log("corrupt PVR file", file->getFileName(), ELL_ERROR);
        return NULL;
    }

    u32 format = header.Flags & 0xff;
    ECOLOR_FORMAT colorFormat = ECF_UNKNOWN;
    switch(format)
    {
    case 0x10 : // OGL_RGBA_4444
        {
            colorFormat = ECF_R4G4B4A4;
        }
        break;

    case 0x01 : // OGL_ARGB_1555
        {
            colorFormat = ECF_A1R5G5B5;
        }
        break;

    case 0x11 : // OGL_RGBA_5551
        {
            colorFormat = ECF_R5G5B5A1;
        }
        break;

    case 0x12 : // OGL_RGBA_8888
        {
            colorFormat = ECF_R8G8B8A8;
        }
        break;

    case 0x13 : // OGL_RGB_565
        {
            colorFormat = ECF_R5G6B5;
        }
        break;

    case 0x15 : // OGL_RGB_888
        {
            colorFormat = ECF_R8G8B8;
        }
        break;

    case 0x16 : // OGL_I_8
        {
            colorFormat = ECF_L8;
        }
        break;

    case 0x17 : // OGL_AI_88
        {
            colorFormat = ECF_L8A8;
        }
        break;

    case 0x18 : // OGL_PVRTC2
        {
            colorFormat = (header.Flags & 0x8000
                ? ECF_COMPRESSED_RGBA_PVRTC_2BPP
                : ECF_COMPRESSED_RGB_PVRTC_2BPP);
        }
        break;

    case 0x19 : // OGL_PVRTC4
        {
            colorFormat = (header.Flags & 0x8000
                ? ECF_COMPRESSED_RGBA_PVRTC_4BPP
                : ECF_COMPRESSED_RGB_PVRTC_4BPP);
        }
        break;

    case 0x1C:
        {
            colorFormat = (header.Flags & detail::EPVRF_ALPHA_IN_TEXTURE
                ? ECF_COMPRESSED_RGBA_PVRTCII_2BPP
                : ECF_COMPRESSED_RGB_PVRTCII_2BPP);
        }
        break;

    case 0x1D:
        {
            colorFormat = (header.Flags & detail::EPVRF_ALPHA_IN_TEXTURE
                ? ECF_COMPRESSED_RGBA_PVRTCII_4BPP
                : ECF_COMPRESSED_RGB_PVRTCII_4BPP);
        }
        break;

    case 0x36:
        {
            colorFormat = ECF_COMPRESSED_ETC1_RGB8;
        }
        break;

    case 0x60:
        {
            colorFormat = (header.Flags & detail::EPVRF_ALPHA_IN_TEXTURE
                ? ECF_COMPRESSED_ETC1_ALPHA_RGB8_A4_NATIVE_DMP
                : ECF_COMPRESSED_ETC1_RGB8_NATIVE_DMP);
        }
        break;

    default :
        {
            os::Printer::log("PVR loader", "unsupported format", ELL_ERROR);
            return NULL;
        }
    }
    
    IImage* result = new CImage(colorFormat,
        core::dimension2d<s32>(header.Width, header.Height),
        data,
        header.DataLength,
        header.MipmapCount,false);

    delete[] data;

    return result;
}

bool readPVRHeader( io::IReadFile* file, detail::SPVRHeader& header )
{
    file->seek(0);
    s32 readCount = file->read(&header, sizeof(detail::SPVRHeader));
    if(readCount != sizeof(detail::SPVRHeader)
        || strncmp(header.PVRTag, "PVR!", 4) != 0
        || header.HeaderLength != sizeof(detail::SPVRHeader)
        || ((header.Flags & detail::EPVRF_HAS_MIPMAPS) != 0 && header.MipmapCount == 0)
        || (header.Flags & detail::EPVRF_CUBE_MAP) != 0 && header.SurfaceCount != 6)
    {
        return false;
    }

    if((header.Flags & detail::EPVRF_HAS_MIPMAPS) != 0
        && core::max_(core::log2i(header.Width),
        core::log2i(header.Height),
        core::log2i((header.Flags & detail::EPVRF_VOLUME_TEXTURE) != 0
        ? header.SurfaceCount
        : 1u)) != header.MipmapCount)
    {
        /*os::Printer::logf(ELL_ERROR,
            "loading %s: incomplete mipmap chain not supported",
            file->getFileName());*/
        return false;
    }
    return true;	
}

bool processPVRHeader(io::IReadFile* file, const detail::SPVRHeader& header, STextureDesc& desc)
{
    if(header.Flags & detail::EPVRF_CUBE_MAP)
    {
        _IRR_DEBUG_BREAK(header.SurfaceCount == 6);
        desc.Type = ETT_CUBE_MAP;
    }
    else if(header.Flags & detail::EPVRF_VOLUME_TEXTURE)
    {
        desc.Type = ETT_3D;
    }
    else
    {
        desc.Type = ETT_2D;
    }
    if((header.Flags & detail::EPVRF_TWIDDLED) != 0)
    {
        desc.Layout = ETL_SWIZZLED;
    }
    else
    {
        desc.Layout = ETL_LINEAR;
    }
    desc.Size.Width = header.Width;
    desc.Size.Height = header.Height;
    desc.Depth = desc.Type == ETT_3D ? header.SurfaceCount : 1;
    desc.WithMipmaps = (header.Flags & detail::EPVRF_HAS_MIPMAPS) != 0;
    _IRR_DEBUG_BREAK(!desc.WithMipmaps || header.MipmapCount > 0);

    if(u32(file->getSize() - sizeof(detail::SPVRHeader))
        != header.DataLength * (desc.Type == ETT_CUBE_MAP ? 6 : 1))
    {
        irrLog("Loading"<< file->getFileName().c_str() <<"file size mismatches header info\n", ELL_ERROR);

        return false;
    }

    switch(header.Flags & detail::EPVRF_FORMAT_MASK)
    {
    case 0x00:
        {
            desc.Format = ECF_A4R4G4B4;
        }
        break;

    case 0x01:
        //case 0x03:
        {
            desc.Format = ECF_A1R5G5B5;
        }
        break;

    case 0x02:
    case 0x13:
        {
            desc.Format = ECF_R5G6B5;
        }
        break;

    case 0x04:
    case 0x15:
        {
            desc.Format = ECF_R8G8B8;
        }
        break;

    case 0x05:
    case 0x1A:
        {
            desc.Format = ECF_B8G8R8A8;
        }
        break;

    case 0x07:
    case 0x16:
        {
            desc.Format = ECF_L8;
        }
        break;

    case 0x08:
    case 0x17:
        {
            desc.Format = ECF_L8A8;
        }
        break;

    case 0x0C:
    case 0x18:
        {
            desc.Format = (header.Flags & detail::EPVRF_ALPHA_IN_TEXTURE
                ? ECF_COMPRESSED_RGBA_PVRTC_2BPP
                : ECF_COMPRESSED_RGB_PVRTC_2BPP);
        }
        break;

    case 0x0D:
    case 0x19:
        {
            desc.Format = (header.Flags & detail::EPVRF_ALPHA_IN_TEXTURE
                ? ECF_COMPRESSED_RGBA_PVRTC_4BPP
                : ECF_COMPRESSED_RGB_PVRTC_4BPP);
        }
        break;

    case 0x1C:
        {
            desc.Format = (header.Flags & detail::EPVRF_ALPHA_IN_TEXTURE
                ? ECF_COMPRESSED_RGBA_PVRTCII_2BPP
                : ECF_COMPRESSED_RGB_PVRTCII_2BPP);
        }
        break;

    case 0x1D:
        {
            desc.Format = (header.Flags & detail::EPVRF_ALPHA_IN_TEXTURE
                ? ECF_COMPRESSED_RGBA_PVRTCII_4BPP
                : ECF_COMPRESSED_RGB_PVRTCII_4BPP);
        }
        break;

    case 0x10:
        {
            desc.Format = ECF_R4G4B4A4;
        }
        break;

    case 0x11:
        //case 0x14:
        {
            desc.Format = ECF_R5G5B5A1;
        }
        break;

    case 0x12:
        {
            desc.Format = ECF_R8G8B8A8;
        }
        break;

    case 0x20:
        {
            desc.Format = (header.Flags & detail::EPVRF_ALPHA_IN_TEXTURE
                ? ECF_COMPRESSED_RGBA_S3TC_DXT1
                : ECF_COMPRESSED_RGB_S3TC_DXT1);
        }
        break;

    case 0x21:
    case 0x22:
        {
            desc.Format = ECF_COMPRESSED_RGBA_S3TC_DXT3;
        }
        break;

    case 0x23:
    case 0x24:
        {
            desc.Format = ECF_COMPRESSED_RGBA_S3TC_DXT5;
        }
        break;

    case 0x2A:
        {
            desc.Format = ECF_A2B10G10R10;
        }
        break;

    case 0x36:
        {
            desc.Format = ECF_COMPRESSED_ETC1_RGB8;
        }
        break;

    case 0x39:
        {
            desc.Format = ECF_A8;
        }
        break;

    case 0x3B:
        {
            desc.Format = ECF_L16;
        }
        break;

    case 0x50:
        {
            desc.Format = ECF_RGBA32F;
        }
        break;

    case 0x53:
        {
            desc.Format = ECF_RGB32F;
        }
        break;

    case 0x56:
        {
            desc.Format = ECF_RGBA16F;
        }
        break;

    case 0x60:
        {
            desc.Format = (header.Flags & detail::EPVRF_ALPHA_IN_TEXTURE
                ? ECF_COMPRESSED_ETC1_ALPHA_RGB8_A4_NATIVE_DMP
                : ECF_COMPRESSED_ETC1_RGB8_NATIVE_DMP);
        }
        break;

    default:
        {
            /*os::Printer::logf(ELL_ERROR,
                "loading %s: pixel format %0x02u not supported",
                file->getFileName(),
                header.Flags & detail::EPVRF_FORMAT_MASK);*/
            return false;
        }
    }

    /*if((header.Flags & detail::EPVRF_TWIDDLED) != 0
        && !pixel_format::isCompressed(desc.Format))
    {
        os::Printer::logf(ELL_ERROR,
            "loading %s: twiddled format not supported",
            file->getFileName());
        return false;
    }*/

    return true;
}

namespace irr { namespace video {

IImageLoader* createImageLoaderPVR()
{
    return new CImageLoaderPVR();
}

}}

