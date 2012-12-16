#ifndef AnimatedGameObject_h__
#define AnimatedGameObject_h__

#include "GameObject.h"
#include "SpriteDefs.h"
#include "SharedPointer.h"

SHARED_PTR_FORWARD(AnimatedGameObject);

class AnimatedGameObject: public GameObject
{
private:
protected:
    SpriteInstance*                        m_Sprite;
public:
    AnimatedGameObject();
    virtual ~AnimatedGameObject();

    // overrides:
    virtual void Update(float dt, const RenderContext& context);
    virtual GameObject::EType       Type() const { return ET_ANIMATED; }
    virtual void                    Serialize(DynamicMemoryStream& dms);
    virtual size_t                  Deserialize(MemoryStream& ms);
    virtual bool_t                  HitTest(const core::position2df& in) const;
};

#endif // AnimatedGameObject_h__
