#include "pch.h"

#include "MemoryStream.h"

#include "Logger.h"
#include "MemoryStreamExceptions.h"

MemoryStream::MemoryStream(const unsigned char *data, unsigned int size)
: m_data(NULL)
, m_size(0)
, m_maxSize(0)
, m_position(0)
{
    if (size != 0)
    {
        try
        {
            m_data = APP_API_NEW unsigned char[size];
        }
        catch (std::bad_alloc &)
        {
            LOGGER->LogMsg(LOG_CRIT, "Unable to allocate memory for stream [%d]", size);
            throw COutOfMemoryException("Out of memory in constructor when allocating stream");
        }
        m_maxSize = size;
        if (data)
        {
            APP_API_MEMCPY(m_data, data, size);
            m_size = size;
        }
    }
}

MemoryStream::~MemoryStream()
{
    APP_API_DELETE_ARRAY(m_data);
}

// Reserves capacity bytes

void MemoryStream::resize(unsigned int maxSize)
{
    if (maxSize <= m_maxSize)
    {
        return;
    }

    unsigned char *newData = NULL;
    try
    {
        newData = APP_API_NEW unsigned char[maxSize];
    }
    catch (std::bad_alloc &)
    {
        LOGGER->LogMsg(LOG_CRIT, "Unable to allocate memory for stream resize[%d->%d]", m_size, maxSize);
        throw COutOfMemoryException("Out of memory when resizing");
        return;
    }

    APP_API_MEMSET(newData, 0, maxSize);
    // If we had any data, copy it over
    APP_API_ASSERT(m_size <= m_maxSize);
    if (m_size > 0)
    {
        APP_API_MEMCPY(newData, m_data, m_size);
    }
    APP_API_DELETE_ARRAY(m_data);

    m_data = newData;
    m_maxSize = maxSize;
}

unsigned char* MemoryStream::GetData() const
{
    return m_data;
}

unsigned int MemoryStream::GetSize() const
{
    return m_size;
}

unsigned int MemoryStream::getMaxSize() const
{
    return m_maxSize;
}

unsigned int MemoryStream::getPosition() const
{
    return m_position;
}

unsigned int MemoryStream::getBytesAvailable() const
{
    if (m_size > m_position)
    {
        return m_size - m_position;
    }

    return 0;
}

void MemoryStream::setSize(unsigned int size)
{
    m_size = size;
    APP_API_ASSERT(m_size <= m_maxSize);
}

void MemoryStream::seek(TSeekPosition seekPosition, int offset)
{
    if (seekPosition == SEEK_POS_START)
    {
        m_position = offset;
    }
    else if (seekPosition == SEEK_POS_END)
    {
        m_position = m_size + offset;
    }
    else if (seekPosition == SEEK_POS_CURR)
    {
        m_position += offset;
    }
}

unsigned int MemoryStream::readUTF8(std::string &str)
{
    unsigned short length;
    unsigned int readBytes = read(&length);

    return readUTF8(str, length) + readBytes;
}

unsigned int MemoryStream::readUTF8(std::string &str, unsigned short length)
{
    if (length == 0)
    {
        return length;
    }

    char *s = NULL;
    try
    {
        s = APP_API_NEW char[length];
        APP_API_MEMSET(s, 0, length);
    }
    catch (std::bad_alloc &)
    {
        LOGGER->LogMsg(LOG_CRIT, "Unable to allocate memory for stream readUTF8 length[%d]", length);
        throw COutOfMemoryException("Out of memory when readUTF8");
    }

    unsigned int readBytes = read(s, length);

    str.assign(s, length);
    //str = core::stringc(s, length);

    APP_API_DELETE_ARRAY(s);

    return readBytes;
}

unsigned int MemoryStream::writeUTF8( const std::string &str )
{
    unsigned short length = static_cast<unsigned short> (str.size());
    unsigned int writeBytes = write(&length);

    return write(str.c_str(), length) + writeBytes;
}

unsigned int MemoryStream::readBytes(char *s, unsigned int count)
{
    if (count == 0 || count < 0)
        return 0;

    //assert(m_position < m_maxSize);
    if (m_position >= m_maxSize)
        throw COutOfRangeException("Reading out of range");

    if (count > (m_maxSize - m_position))
    {
        count = m_maxSize - m_position;
    }

    APP_API_MEMCPY(s, &m_data[ m_position ], count);

    m_position += count;

    APP_API_ASSERT(m_position <= m_maxSize);

    return count;
}

unsigned int MemoryStream::writeBytes(const char *s, unsigned int count)
{
    if (count == 0)
    {
        return count;
    }

    if (m_position >= m_maxSize)
    {
        onWriteOOR(count);
    }

    if (count < 0)
    {
        count = 0;
        return count;
    }
    else if (count > (m_maxSize - m_position))
    {
        onWriteOOR(count);
    }

    APP_API_MEMCPY(&m_data[ m_position ], s, count);

    m_position += count;
    if (m_position > m_size)
    {
        m_size = m_position;
    }

    APP_API_ASSERT(m_size <= m_maxSize);
    return count;
}

void MemoryStream::onWriteOOR(unsigned int count)
{
    throw COutOfRangeException("Writing out of range");
}

void MemoryStream::clean()
{
    APP_API_MEMSET(m_data, 0, m_size);
    m_position = 0;
}
