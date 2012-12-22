//mmgr checked
#pragma once
#ifndef __DYNAMIC_MEMORY_STREAM_H__
#    define __DYNAMIC_MEMORY_STREAM_H__

#    include "MemoryStream.h"

// MemoryStream that automatically grows on Write OOR conditions

class DynamicMemoryStream : public MemoryStream
{
public:
    DynamicMemoryStream(const unsigned char *data = NULL, unsigned int size = 0);
    virtual ~DynamicMemoryStream();

    bool_t Inflate();

protected:
    void onWriteOOR(unsigned int count);

private:
    unsigned int roundToNextPowerof2(unsigned int x);

    int tryInflate(DynamicMemoryStream &dest);
} ;

#endif