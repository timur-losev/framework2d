#include "pch.h"

#    include "MemoryStream.h"
#    include "BoundedBufferReader.h"

BoundedBufferReader::BoundedBufferReader(MemoryStream *buffer, int version, int *maxSize)
: m_buffer(buffer)
, m_version(version)
, m_maxSize(maxSize)
{
}

BoundedBufferReader::~BoundedBufferReader()
{
    m_maxSize = NULL;
}

unsigned int BoundedBufferReader::readUTF8(FString &str)
{
    if (!m_maxSize)
    {
        return m_buffer->readUTF8(str);
    }

    // Check bound
    if (*m_maxSize <= 0)
    {
        // Do nothing
        return 0;
    }

    unsigned short length;
    unsigned int readBytes = m_buffer->read(&length);

    // Check that we can read this string
    if (*m_maxSize < length)
    {
        return 0;
    }

    int count = m_buffer->readUTF8(str, length) + readBytes;
    *m_maxSize -= count;
    return count;
}