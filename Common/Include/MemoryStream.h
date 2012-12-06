#ifndef __MEMORY_STREAM_H__
#    define __MEMORY_STREAM_H__

// Memory stream abstraction.
// It is thought to be used as a fixed size memory stream.

class MemoryStream
{
public:

    enum TSeekPosition
    {
        SEEK_POS_START = 0,
        SEEK_POS_END,
        SEEK_POS_CURR,
    } ;

public:
    /// @param data pointer to the data
    /// @param size size of the data in bytes
    /// If default values are used, an empty memory stream is created
    MemoryStream(const unsigned char *data = NULL, unsigned int size = 0);
    virtual ~MemoryStream();

    void resize(unsigned int maxSize);

    unsigned int GetSize() const;
    unsigned int getMaxSize() const;
    unsigned int getPosition() const;
    unsigned int getBytesAvailable() const;

    unsigned char* GetData() const;
    // This function must be called explicitly to reflect changes in the buffer done externally (through getData)
    void setSize(unsigned int size);

    void seek(TSeekPosition seekPosition, int offset = 0);

    template < class T >
    unsigned int read( T *s, unsigned int elementsCount = 1 )
    {
        return readBytes( reinterpret_cast< char* > ( s ), elementsCount * sizeof ( T ) );
    }

    template < class T >
    unsigned int write( const T *s, unsigned int elementsCount = 1 )
    {
        return writeBytes( reinterpret_cast< const char* > ( s ), elementsCount * sizeof ( T ) );
    }

    // Read a utf-8 string in which the first 2 bytes are 16-bit int representing the total lenght of the string to read
    unsigned int readUTF8(std::string &str);

    // Read a utf-8 string of the specified length
    unsigned int readUTF8(std::string &str, unsigned short length);

    // Write an utf-8 string, writing the length at the beginning using 2 bytes
    unsigned int writeUTF8(const std::string &str);

    void clean();

protected:
    unsigned int readBytes(char *s, unsigned int count);
    unsigned int writeBytes(const char *s, unsigned int count);

    virtual void onWriteOOR(unsigned int count);

protected:
    unsigned char *m_data;
    // Size of the data in the buffer
    unsigned int m_size;
    // Size of the allocated buffer
    unsigned int m_maxSize;
    unsigned int m_position;
} ;

#endif