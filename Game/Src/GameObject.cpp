#include "EdPrec.h"

#include "GameObject.h"
#include "Sprite.h"

GameObject::GameObject():
    m_Hash(0)
{
    m_SpriteInstance.reset(new SpriteInstance());
}

GameObject::GameObject( const core::position2df& pos, const core::vector2df& scale, float rot, const std::string& name ):
    m_Name(name),
    m_Hash(0)
{
    m_SpriteInstance.reset(new SpriteInstance());
    m_SpriteInstance->SetPosition(pos);
    m_SpriteInstance->SetScale(scale);
    m_SpriteInstance->SetRotation(rot);
}

GameObject::GameObject( const GameObject& oth )
    :
    m_Name(oth.m_Name),
    m_Hash(oth.m_Hash)
{

}

GameObject::~GameObject()
{

}

void GameObject::Init()
{
    Hash(); //Calc hash here
}

hash_t GameObject::Hash()
{
    if (m_Hash == 0)
        m_Hash = CalcHash();

    return m_Hash;
}

hash_t GameObject::CalcHash()
{
    return APP_API_STRHASH(m_Name.c_str(), m_Name.size());
}

GameObject& GameObject::operator=( const GameObject& oth )
{
    //TODO

    /*m_Position = oth.m_Position;
    m_Scale = oth.m_Scale;
    m_Rotation = oth.m_Rotation;
    m_Name = oth.m_Name;
    m_Hash = oth.m_Hash;*/

    return *this;
}

bool_t GameObject::operator==( const GameObject& oth )
{
    return oth.m_Hash != 0 && oth.m_Hash == Hash();
}

void GameObject::Update( float dt, const RenderContext& context )
{
#ifdef USE_INVOKER
    UpdateInvoker();
#endif

    m_SpriteInstance->Update(dt, context);

    std::for_each(m_Childs.begin(), m_Childs.end(), [&](GameObjectPtr obj)
        {
            obj->Update(dt, context);
        }
    );

    if (m_SpriteInstance->IsEmpty())
    {
        m_SpriteInstance->Load(EMPTY_STUB);
    }
}

void GameObject::Serialize( DynamicMemoryStream& dms )
{
    //TODO:
    dms.writeUTF8(m_Name);
    m_SpriteInstance->Serialize(dms);
}

size_t GameObject::Deserialize( MemoryStream& ms )
{
    //TODO:
    size_t read = 0;
    read = ms.readUTF8(m_Name);
    read += m_SpriteInstance->Deserialize(ms);

    return read;
}

const core::position2df& GameObject::GetPosition(EPosRelation r) const
{
    return m_SpriteInstance->GetPosition(r);
}

void GameObject::SetPosition( const core::position2df& val, EPosRelation r)
{
    m_SpriteInstance->SetPosition(val, r);
}

const std::string& GameObject::GetName()
{
    return m_Name;
}

void GameObject::SetName( const std::string& val )
{
    m_Name = val;
}

const core::vector2df& GameObject::GetScale()
{
    return m_SpriteInstance->GetScale();
}

void GameObject::SetScale( const core::vector2df& val )
{
    m_SpriteInstance->SetScale(val);
}

float GameObject::GetRotation()
{
    return m_SpriteInstance->GetRotation();
}

void GameObject::SetRotation( float val )
{
    m_SpriteInstance->SetRotation(val);
}

bool_t GameObject::HitTest( const core::position2df& in ) const
{
    const core::position2df& thispos = GetPosition(ABSOLUTE_POS);
    if (in.X < thispos.X || in.Y < thispos.Y)
        return FALSE;

    if (m_SpriteInstance->HitTest(in))
        return TRUE;

    for(GameObjectList_t::const_iterator i = m_Childs.begin(), e = m_Childs.end(); i != e; ++i)
    {
        if ((*i)->HitTest(in))
            return TRUE;
    }

    return FALSE;
}

SpriteInstancePtr GameObject::GetSprite()
{
    return m_SpriteInstance;
}

SpriteInstanceConstPtr GameObject::GetSprite() const
{
    return m_SpriteInstance;
}

void GameObject::SetSprite( SpriteInstancePtr sprite )
{
    m_SpriteInstance = sprite;
}

GameObjectPtr GameObject::GetParent()
{
    return m_Parent;
}

void GameObject::SetParent( GameObjectPtr o)
{
    m_Parent = o;
}

void GameObject::AddChild( GameObjectPtr o)
{
    APP_API_ASSERT(GetChild(o->GetName()) == nullptr);

    o->SetParent(shared_from_this());
    m_Childs.push_back(o);
}

void GameObject::AddChild( GameObjectPtr o, int index )
{
    APP_API_ASSERT(GetChild(o->GetName()) == nullptr);

    GameObjectListIter_t i = m_Childs.begin();
    std::advance(i, index);
    o->SetParent(shared_from_this());
    m_Childs.insert(i, o);
}

void GameObject::RemoveChild( GameObjectPtr o)
{
    //TODO:

    ///
    o->SetParent(nullptr);
}

GameObjectPtr GameObject::GetChild( const std::string& name )
{
    //TODO: hashify names if performance stuck at this
    for(GameObjectList_t::const_iterator i = m_Childs.begin(), e = m_Childs.end(); i != e; ++i)
    {
        if ((*i)->GetName() == name)
            return *i;
    }

    return nullptr;
}
