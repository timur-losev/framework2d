#ifndef __PAGE_H__
#    define __PAGE_H__

#    include "GameObject.h"
#    include "Serializable.h"

enum ePageLayer
{
    EPAGE_LAYER_BOTTOM = 0,
    EPAGE_LAYER_MIDDLE,
    EPAGE_LAYER_TOP,
    EPAGE_LAYER_MAX
} ;

#    ifdef USE_INVOKER
#        include "Invoker.h"
class CPage : public Serializable, public Common::Invoker
#    else

class CPage : public Serializable
#    endif
{
private:
protected:
    core::rectf		    m_Bound;
    core::position2df	    m_Pos;
    u32			    m_Index;
    core::position2df	    m_Offset;

    GameObjectList_t	    m_Layers[EPAGE_LAYER_MAX];
    GameObjectListIter_t    m_GameObjectsIter;
    bool_t                  m_DirtyPos;
public:

    bool_t                  Init(size_t index);
    void                    Update(float dt, DriverPtr driver);
    void                    Destroy();

    INL const core::rectf& GetBound() const
    {
        return m_Bound;
    }

    INL u32 GetIndex() const
    {
        return m_Index;
    }

    INL const core::position2df& GetPosition() const
    {
        return m_Pos;
    }

    INL void SetPosition(const core::position2df& pos)
    {
        m_Pos = pos;
    }

    void                     Scroll(float stepX, float stepY);

    bool_t                   HitTest(const core::position2df& pos);

    GameObjectPtr            GetGameObjectByName(const std::string& name);
    GameObjectPtr            GetGameObjectByHash(hash_t hash);
    GameObjectPtr            GetGameObjectByPoint(const core::position2df& p);
    bool_t		     AddGameObject(GameObjectPtr obj, const ePageLayer layer = EPAGE_LAYER_MIDDLE);
    GameObjectPtr	     AddGameObject(const std::string& name, GameObject::EType type, const ePageLayer layer = EPAGE_LAYER_MIDDLE);
    GameObjectListIter_t     RemoveGameObject(GameObjectPtr obj, const ePageLayer layer = EPAGE_LAYER_MIDDLE);

    const GameObjectList_t&  GetObjects(const ePageLayer layer = EPAGE_LAYER_MIDDLE) const;
    GameObjectList_t&        GetObjects(const ePageLayer layer = EPAGE_LAYER_MIDDLE);

    virtual void             Serialize(DynamicMemoryStream& dms);
    virtual size_t           Deserialize(MemoryStream& ms);

    static core::dimension2df   PageSize;

    CPage();
    ~CPage();

public:

    static float			BackgroundLayerSpeed;
    static core::position2df		MainLayerSpeed;
    static float			ForegroundLayerSpeed;
} ;

#endif // __PAGE_H__