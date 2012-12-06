#ifdef EDITOR
#include "EdPrec.h"
#else
#include "Prec.h"
#endif

#include "ILevel.h"

hash_t ILevel::GetHash()
{
    return (hash_t)this;
}

const std::string& ILevel::GetName() const
{
    return m_StringID;
}
