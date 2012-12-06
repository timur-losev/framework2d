#ifndef CImageLoaderPVR_h__
#define CImageLoaderPVR_h__

#include "IrrCompileConfig.h"

#ifdef _IRR_COMPILE_WITH_PVR_LOADER_

#include "IImageLoader.h"


namespace irr { namespace video {

    namespace detail
    {
        struct SPVRHeader;
    }

    class CImageLoaderPVR: public IImageLoader
    {
    public:
        virtual bool isALoadableFileExtension(const io::path& filename) const;
        virtual bool isALoadableFileFormat(io::IReadFile* file) const;
        virtual IImage* loadImage(io::IReadFile* file) const;
    };
}}

#endif //_IRR_COMPILE_WITH_PVR_LOADER_

#endif // CImageLoaderPVR_h__
