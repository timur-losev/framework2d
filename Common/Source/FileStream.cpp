/*
 * File:   FileStream.cpp
 * Author: void
 *
 * Created on June 19, 2011, 12:59 AM
 */

#include "pch.h"

#include "FileStream.h"
#include "Logger.h"

FileStream::FileStream() :
DynamicMemoryStream(NULL, DEFAULT_BUF_SIZE)
, m_Accessor(FAUNKNOWN)
, m_pFile(NULL)
, m_Flushed(FALSE)
, m_Closed(TRUE)
{
}

FileStream::~FileStream()
{
    CloseStream();
}

void FileStream::Close()
{
    CloseStream();
}

void FileStream::CloseStream()
{
    if (m_Closed != FALSE) return;

    if (m_Accessor & WRITE_BINARY)
    {
        Flush();
    }

    if (m_pFile)
    {
        fclose(m_pFile);
        m_pFile = NULL;
    }

    m_Flushed = FALSE;
    m_Closed = TRUE;
}

// BUG: once flushed buffer -> need reopening the handle

void FileStream::Flush()
{
    if (m_Flushed || (m_Accessor & READ_BINARY)) return;

    APP_API_ASSERT(m_data && m_pFile && m_size);

    fwrite(m_data, m_size, 1, m_pFile);

    m_Flushed = TRUE;
}

bool_t FileStream::FromFile(const std::string& path, FILE_ACCESSOR accessor)
{
    CloseStream();

    m_Path = path;

    std::string acc = "rb";

    m_Accessor = accessor;

    if (m_Accessor & WRITE_BINARY)
    {
        acc = "wb";
    }

    //Only one accessor
    APP_API_ASSERT(((m_Accessor & READ_BINARY) & (m_Accessor & WRITE_BINARY)) == 0);

    m_pFile = fopen(m_Path.c_str(), acc.c_str());

    if (!m_pFile)
    {
        LOGGER->LogMsg(LOG_ERR, "FileStream: Fail with opening the file [%s]", path.c_str());
        return FALSE;
    }

    m_Closed = FALSE;

    ReadBuffer();

    return TRUE;
}

void FileStream::ReadBuffer()
{
    if ((m_Accessor & READ_BINARY) == 0) return;

    fseek(m_pFile, 0, SEEK_END);
    unsigned int lsize = ftell(m_pFile);
    rewind(m_pFile);

    if (lsize > m_maxSize)
    {
        onWriteOOR(lsize - m_maxSize);
    }

    size_t l = fread(m_data, lsize, 1, m_pFile);
    (void)l;

    m_size = lsize;

    m_position = 0;
}