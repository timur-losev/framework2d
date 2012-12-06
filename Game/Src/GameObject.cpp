#include "EdPrec.h"

#include "GameObject.h"

GameObject::GameObject():
    m_Rotation(0.0f),
    m_Scale(1, 1),
    m_Hash(0)
{

}

GameObject::GameObject( const core::position2df& pos, const core::vector2df& scale, float rot, const std::string& name ):
    m_Position(pos),
    m_Shift(0.f),
    m_Rotation(rot),
    m_Scale(scale),
    m_Name(name),
    m_Hash(0)
{

}

GameObject::GameObject( const GameObject& oth ):
    m_Position(oth.m_Position),
    m_Shift(oth.m_Shift),
    m_Rotation(oth.m_Rotation),
    m_Scale(oth.m_Scale),
    m_Name(oth.m_Name),
    m_Hash(oth.m_Hash),
    m_Offset(oth.m_Offset)
{

}

GameObject::~GameObject()
{

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
    m_Position = oth.m_Position;
    m_Scale = oth.m_Scale;
    m_Rotation = oth.m_Rotation;
    m_Name = oth.m_Name;
    m_Hash = oth.m_Hash;

    return *this;
}

bool_t GameObject::operator==( const GameObject& oth )
{
    return oth.m_Hash != 0 && oth.m_Hash == Hash();
}

void GameObject::Update(float dt, DriverPtr driver)
{
#ifdef USE_INVOKER
    UpdateInvoker();
#endif
}

void GameObject::Serialize( DynamicMemoryStream& dms )
{
    dms.writeUTF8(m_Name);
    dms.write(&m_Position.X);
    dms.write(&m_Position.Y);
    dms.write(&m_Rotation);
    dms.write(&m_Scale.X);
    dms.write(&m_Scale.Y);
}

size_t GameObject::Deserialize( MemoryStream& ms )
{
    size_t read = 0;
    read = ms.readUTF8(m_Name);

    read += ms.read(&m_Position.X);
    read += ms.read(&m_Position.Y);
    read += ms.read(&m_Rotation);
    read += ms.read(&m_Scale.X);
    read += ms.read(&m_Scale.Y);

    return read;
}
