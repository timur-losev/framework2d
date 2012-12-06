#ifndef StaticGameObject_h__
#define StaticGameObject_h__

#include "GameObject.h"
#include "SpriteDefs.h"

class StaticGameObject: public GameObject
{
public:
    struct GraphicItem
    {
        video::ITexture*        m_Image;
        core::recti             m_SourceRect;       //=from which to draw (pre-calculated. It may be received from m_FrameInfo components)
        core::rectf             m_DestRect;     //=where draw
        FrameDef                m_FrameInfo;
    };

    typedef std::list<GraphicItem>              GraphicState_t;
    typedef GraphicState_t::iterator        GraphicStateIter_t;
    typedef GraphicState_t::const_iterator  GraphicStateConstIter_t;
private:

protected:
    GraphicState_t      m_GraphicState;
    GraphicStateIter_t  m_GraphicStateIterBegin;
    GraphicStateIter_t  m_GraphicStateIterEnd;
    DriverPtr           m_Driver;
public:
    typedef StaticGameObject* Ptr;

    StaticGameObject();
    virtual ~StaticGameObject();

    virtual void                 Update(float dt, DriverPtr driver);
    virtual GameObject::EType    Type() const { return ET_STATIC; }

    INL const GraphicState_t&    GraphicState() const { return m_GraphicState; }
    void                         AddGraphicItem(const std::string& texture, const FrameDef& frame);

    virtual void                 Serialize(DynamicMemoryStream& dms);
    virtual size_t               Deserialize(MemoryStream& ms);
    virtual bool_t               HitTest(const core::position2df& in) const;
};

#endif // StaticGameObject_h__
