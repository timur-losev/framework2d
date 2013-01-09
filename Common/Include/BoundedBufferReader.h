#ifndef __BOUNDED_BUFFER_READER_H__
#    define __BOUNDED_BUFFER_READER_H__

class MemoryStream;

class BoundedBufferReader
{
public:
    BoundedBufferReader(MemoryStream *buffer, int version, int *maxSize);
    ~BoundedBufferReader();

    template < class T >
    unsigned int read( T *s, unsigned int elementsCount = 1 )
    {
	if (!m_maxSize)
	{
	    return m_buffer->read(s, elementsCount);
	}

	// Check bound
	if (*m_maxSize <= 0 || *m_maxSize < (int) (sizeof (T) * elementsCount))
	{
	    // Do nothing
	    return 0;
	}

	int count = m_buffer->read(s, elementsCount);
	*m_maxSize -= count;
	return count;
    }

    unsigned int readUTF8(FString &str);

private:
    MemoryStream *m_buffer;
    int m_version;
    int *m_maxSize;
} ;

#endif
