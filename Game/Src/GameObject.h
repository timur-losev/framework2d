#ifndef GameObject_h__
#    define GameObject_h__

#    include "Serializable.h"
#    include "SharedPointer.h"

SHARED_PTR_FORWARD(GameObject);

#    ifdef USE_INVOKER
#        include <Invoker.h>
class GameObject : public Serializable, public Common::Invoker
#    else

class GameObject : public Serializable
#    endif
{
public:

    enum EType
    {
        ET_NONE = 0,
        ET_STATIC,
        ET_ANIMATED
    } ;

private:
protected:
    core::position2df       m_Position;
    core::position2df       m_Shift;
    float                   m_Rotation; //degrees
    core::vector2df         m_Scale;
    std::string           m_Name;
    hash_t                  m_Hash;
    virtual hash_t          CalcHash();
    core::position2df		m_Offset;
public:

    GameObject();

    GameObject(const core::position2df& pos, const core::vector2df& scale,
               float rot, const std::string& name);

    GameObject(const GameObject& oth);

    virtual ~GameObject();

    INL core::position2df&       Position()
    {
        return m_Position;
    }

    INL void                     Position(const core::position2df& val)
    {
        m_Position = val;
    }

    INL std::string&           Name()
    {
        return m_Name;
    }

    INL void                     Name(const std::string& val)
    {
        m_Name = val;
    }

    INL core::vector2df&         Scale()
    {
        return m_Scale;
    }

    INL void                     Scale(const core::vector2df& val)
    {
        m_Scale = val;
    }

    INL float                    Rotation()
    {
        return m_Rotation;
    }

    INL void                     Rotation(float val)
    {
        m_Rotation = val;
    }

    INL core::position2df&       Offset()
    {
        return m_Offset;
    }

    INL void                     Offset(const core::position2df& val)
    {
        m_Offset = val;
    }

    virtual hash_t               Hash();

    virtual void                 Update(float dt, DriverPtr driver);

    virtual EType                Type() const
    {
        return ET_NONE;
    }

    virtual void                 Serialize(DynamicMemoryStream& dms);
    virtual size_t               Deserialize(MemoryStream& ms);

    GameObject& operator=(const GameObject& oth);
    bool_t operator==(const GameObject& oth);

    INL StaticGameObject*        AsStaticGameObject()
    {
        APP_API_ASSERT(Type() == ET_STATIC);
        return (StaticGameObject*)this;
    }

    INL AnimatedGameObject*      AsAnimatedGameObject()
    {
        APP_API_ASSERT(Type() == ET_ANIMATED);
        return (AnimatedGameObject*)this;
    }

    virtual bool_t               HitTest(const core::position2df& in) const
    {
        return FALSE;
    }
} ;

typedef std::list<GameObjectPtr>                 GameObjectList_t;
typedef GameObjectList_t::iterator				GameObjectListIter_t;

#endif // GameObject_h__
