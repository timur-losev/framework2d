/*#### ##       ######## ##     ## ######## ##
   ##  ##       ##       ##     ## ##       ##
   ##  ##       ##       ##     ## ##       ##
   ##  ##       ######   ##     ## ######   ##
   ##  ##       ##        ##   ##  ##       ##
   ##  ##       ##         ## ##   ##       ##
  #### ######## ########    ###    ######## ######## */

#ifndef ILevel_h__
#define ILevel_h__

#include "Serializable.h"
#include "Prec.h"
#include "Invoker.h"

#ifdef USE_INVOKER
class ILevel: public Serializable, public Common::Invoker
#else
class ILevel: public Serializable
#endif
{
protected:
    std::string             m_StringID; // just name
    hash_t                  m_Hash;

public:
    virtual ~ILevel() {}
    ILevel(const std::string& name): m_StringID(name), m_Hash(0)  {}

    virtual hash_t                          GetHash();
    virtual const std::string&             GetName() const;

    virtual void            Update(float dt, DriverPtr driver) = 0;
    virtual bool_t          Create() = 0;
    virtual void            Init() = 0;
    virtual void            Destroy() = 0;
};

#endif // ILevel_h__
