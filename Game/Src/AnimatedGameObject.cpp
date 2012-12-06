#ifdef EDITOR
#include "EdPrec.h"
#else
#include "Prec.h"
#endif

#include "AnimatedGameObject.h"
#include "Sprite.h"

AnimatedGameObject::AnimatedGameObject()
{
    m_Sprite = APP_API_NEW CSprite();
}

AnimatedGameObject::~AnimatedGameObject()
{
    APP_API_DEL(m_Sprite);
}

void AnimatedGameObject::Update(float dt, DriverPtr driver)
{
    m_Sprite->SetPosition(m_Position);
    m_Sprite->SetRotation(m_Rotation);
    m_Sprite->SetScale(m_Scale);

    m_Sprite->Update(driver);
}

void AnimatedGameObject::Serialize( DynamicMemoryStream& dms )
{

}

size_t AnimatedGameObject::Deserialize( MemoryStream& ms )
{
    return 0;
}

bool_t AnimatedGameObject::HitTest( const core::position2df& in ) const
{
    return 0;
}


