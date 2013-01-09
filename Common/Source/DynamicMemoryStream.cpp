#include "pch.h"

#include "DynamicMemoryStream.h"

#    if USE_ZLIB
#ifdef FAR
#undef FAR
#define FAR
#endif
#        include <zlib.h>
#    endif

DynamicMemoryStream::DynamicMemoryStream(const unsigned char *data, unsigned int size)
: MemoryStream(data, size)
{
}

DynamicMemoryStream::~DynamicMemoryStream()
{
}

void DynamicMemoryStream::onWriteOOR(unsigned int count)
{
    resize(roundToNextPowerof2((m_maxSize + count) << 1));
}

//NOTE: Create and move this function to MathUtils if needed

unsigned int DynamicMemoryStream::roundToNextPowerof2(unsigned int x)
{
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    return x + 1;
}

bool_t DynamicMemoryStream::Inflate()
{
    DynamicMemoryStream* tempBuf = new DynamicMemoryStream(NULL, this->GetSize());

    bool_t status = TRUE;

    if (tryInflate(*tempBuf) != 0/*Z_OK*/)
    {
        status = FALSE;
    }
    else
    {
        clean();

        write(tempBuf->GetData(), tempBuf->GetSize());
    }

    APP_API_DEL(tempBuf);

    return status;
}

int DynamicMemoryStream::tryInflate(DynamicMemoryStream &dest)
{
#if USE_ZLIB
    int ret;
    z_stream strm;

    const int BlkSize = 32767;

    Bytef in[BlkSize];
    Bytef out[BlkSize];

    memset(&strm, Z_NULL, sizeof (z_stream));

    ret = ::inflateInit2(&strm, 31);
    if (ret != Z_OK) return ret;

    do
    {
        strm.avail_in = read(in, BlkSize);

        if (strm.avail_in == 0)
            break;

        strm.next_in = in;

        do
        {
            strm.avail_out = BlkSize;
            strm.next_out = out;


            ret = ::inflate(&strm, Z_NO_FLUSH);
            APP_API_ASSERT(ret != Z_STREAM_ERROR);

            switch (ret)
            {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                inflateEnd(&strm);
                return ret;
            }

            //NOTE: Control here for out = 1byte! It's important.
            if (dest.write(out, BlkSize - strm.avail_out) < 0)
            {
                ::inflateEnd(&strm);
                return Z_ERRNO;
            }
        }

        while (strm.avail_out == 0);
    }
    while (ret != Z_STREAM_END);

    ::inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
#else
    return 1;
#endif
}