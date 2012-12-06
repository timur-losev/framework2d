/*
 * File:   FileStream.h
 * Author: void
 *
 * Created on June 19, 2011, 12:59 AM
 */

#ifndef FILESTREAM_H
#    define	FILESTREAM_H

#    include "DynamicMemoryStream.h"

#    define DEFAULT_BUF_SIZE 1024*32
//#define DEFAULT_BUF_SIZE 8

class FileStream : public DynamicMemoryStream
{
private:
    FileStream(const FileStream& orig);
    FileStream& operator=(FileStream&);
protected:
    FILE_ACCESSOR           m_Accessor;

    FILE*                   m_pFile;
    std::string             m_Path; //TODO: WString or Path_t

    bool_t                  m_Flushed;
    bool_t                  m_Closed;

    void                    CloseStream();
    void                    ReadBuffer();
public:

    FileStream();

    bool_t                  FromFile(const std::string& path, FILE_ACCESSOR accessor);

    virtual ~FileStream();
    void                    Flush();

    void                    Close();
} ;

#endif	/* FILESTREAM_H */

