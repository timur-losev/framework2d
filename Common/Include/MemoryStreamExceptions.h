#ifndef __MEMORY_STREAM_EXCEPTIONS_H__
#    define __MEMORY_STREAM_EXCEPTIONS_H__

class COutOfRangeException : public std::runtime_error
{
public:

    COutOfRangeException(const std::string &msg)
    : std::runtime_error(msg) { }
} ;

class COutOfMemoryException : public std::runtime_error
{
public:

    COutOfMemoryException(const std::string &msg)
    : std::runtime_error(msg) { }
} ;

#endif