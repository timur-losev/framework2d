#ifndef Serializable_h__
#define Serializable_h__

class DynamicMemoryStream;
class MemoryStream;

#include "AppApi.h"

struct Serializable
{
    virtual void Serialize(DynamicMemoryStream& dms)
    {
        APP_API_ASSERT(FALSE && "This object is not support serialization");
    };

    virtual size_t Deserialize(MemoryStream& ms)
    {
        APP_API_ASSERT(FALSE && "This object is not support serialization"); return 0;
    }

    virtual void Deserialize_stub(MemoryStream& ms)
    {
        Deserialize(ms);
    }
};

#endif // Serializable_h__
