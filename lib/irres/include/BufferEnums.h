#ifndef BufferEnums_h__
#define BufferEnums_h__

namespace irr { namespace video {

    //!
    enum E_BUFFER_TYPE
    {
        //!
        EBT_VERTEX,

        //!
        EBT_INDEX,

        //!
        EBT_PIXEL_PACK,

        //!
        EBT_PIXEL_UNPACK,

        //!
        EBT_TEXTURE_REFERENCE,

        //! 3DS's implementation of VAO
        EBT_VERTEX_STATE_COLLECTION,

        EBT_COUNT,
        EBT_UNKNOWN = u8(-1)
    };

    //!
    enum E_BUFFER_USAGE
    {
        //!
        EBU_STATIC,

        //!
        EBU_DYNAMIC,

        //!
        EBU_STREAM,

        //!
        EBU_SYSTEM,

        //!
        EBU_NONE,

        EBU_COUNT,
        EBU_UNKNOWN = u8(-1)
    };

    enum E_BUFFER_READ_MAP_ACCESS
    {
        //!
        EBMA_READ = 0,

        //!
        EBMA_READ_CLIENT = 1,

        EBMA_READ_COUNT = 2
    };

    enum E_BUFFER_MAP_ACCESS
    {
        //!
        EBMA_WRITE = 2,

        //!
        EBMA_READ_WRITE = 3,

        //!
        EBMA_WRITE_CLIENT = 4,

        //!
        EBMA_READ_WRITE_CLIENT = 5,

        EBMA_COUNT = 6,

        EBMA_UNKNOWN = u8(-1)
    };

}}

#endif // BufferEnums_h__
