#ifndef GameObject_h__
#    define GameObject_h__

#    include "Serializable.h"

SHARED_PTR_FORWARD(GameObject);
SHARED_PTR_FORWARD(SpriteInstance);

typedef std::list<GameObjectPtr>                 GameObjectList_t;
typedef GameObjectList_t::iterator               GameObjectListIter_t;

#    ifdef USE_INVOKER
#    include <Invoker.h>
class GameObject : 
    public Serializable, 
    public Common::Invoker, 
    public std::enable_shared_from_this<GameObject>
#    else

class GameObject : public Serializable, public std::enable_shared_from_this<GameObject>
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
    std::string             m_Name;
    hash_t                  m_Hash;

    core::position2df       m_Offset;

    hash_t                  CalcHash();

    GameObjectList_t        m_Childs;
    GameObjectPtr           m_Parent;

    SpriteInstancePtr       m_SpriteInstance;
public:

    GameObject();

    GameObject(const core::position2df& pos, const core::vector2df& scale,
               float rot, const std::string& name);

    GameObject(const GameObject& oth);

    virtual ~GameObject();

    const core::position2df& GetPosition();
    void                     SetPosition(const core::position2df& val);
    
    const std::string&       GetName();
    void                     SetName(const std::string& val);
    
    const core::vector2df&   GetScale();
    void                     SetScale(const core::vector2df& val); 
    
    float                    GetRotation();
    void                     SetRotation(float val);
    
    const core::position2df& GetOffset();
    void                     SetOffset(const core::position2df& val);

    virtual hash_t           Hash();

    virtual void             Update(float dt, const RenderContext& context);

    virtual EType            Type() const;

    virtual void             Serialize(DynamicMemoryStream& dms);
    virtual size_t           Deserialize(MemoryStream& ms);

    GameObject&              operator=(const GameObject& oth);
    bool_t                   operator==(const GameObject& oth);
    virtual bool_t           HitTest(const core::position2df& in) const;

    SpriteInstancePtr        GetSprite();
    SpriteInstanceConstPtr   GetSprite() const;

    void                     SetSprite(SpriteInstancePtr sprite);

    GameObjectPtr            GetParent();
    void                     SetParent(GameObjectPtr);
    void                     AddChild(GameObjectPtr);
    void                     AddChild(GameObjectPtr, int index);
    void                     RemoveChild(GameObjectPtr);
    GameObjectPtr            GetChild(const std::string& name);
} ;

#endif // GameObject_h__
