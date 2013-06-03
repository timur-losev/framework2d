#include "EdPrec.h"

#include "Page.h"
#include "StaticGameObject.h"
#include "AnimatedGameObject.h"

core::dimension2df	PageInstance::PageSize = core::dimension2df(960.f, 480.f);
float				PageInstance::BackgroundLayerSpeed = 2.f;
core::position2df	PageInstance::MainLayerSpeed		= core::position2df(5.f, 5.f);
float				PageInstance::ForegroundLayerSpeed = 7.f;

PageInstance::PageInstance()
    : m_PageIndex(PE_UINT_MAX)
    , m_DirtyPos(FALSE)
{
}

PageInstance::~PageInstance()
{
    Destroy();
}

void PageInstance::Update( float dt, const RenderContext& context )
{
#ifdef USE_INVOKER
    UpdateInvoker();
#endif

    if (m_DirtyPos)
    {
        m_Pos += m_Offset;
        m_DirtyPos = FALSE;
        m_Offset = core::position2df(0, 0);
    }

    for (int i = 0; i < EPAGE_LAYER_MAX; ++i)
    {
        GameObjectList_t& objects_list = m_Layers[(EPageLayer)i];

        for(GameObjectList_t::iterator i = objects_list.begin(), e = objects_list.end(); i != e; ++i)
        {
            auto obj = *i;

            //if (m_DirtyPos)
            {
                //obj->SetOffset(obj->GetOffset() + m_Offset);
                obj->SetPosition(obj->GetPosition(RELATIVE_POS) + m_Pos, ABSOLUTE_POS);
            }
            obj->Update(dt, context);
        }
    }
}

void PageInstance::Destroy()
{
    /*for (int i = 0; i < EPAGE_LAYER_MAX; ++i)
    {
    GameObjectList_t& objects_list = m_Layers[(EPageLayer)i];

    for(auto obji = objects_list.begin(),
    auto obje = objects_list.end(); obji != obje; ++obji)
    {
    APP_API_DEL(*obji);
    }

    m_Layers[(EPageLayer)i].clear();
    }*/
}

bool_t PageInstance::Init(size_t index)
{
    m_PageIndex = index;
    m_Pos.Y = 0;
    m_Pos.X = index * PageSize.Width;
    m_Bound = core::rectf(m_Pos, PageSize);

    return TRUE;
}

const GameObjectList_t& PageInstance::GetObjects( const EPageLayer layer ) const
{
    return m_Layers[layer];
}

GameObjectList_t& PageInstance:: GetObjects(const EPageLayer layer)
{
    return m_Layers[layer];
}

bool_t PageInstance::HitTest( const core::position2df& pos )
{
    return (m_Pos.X <= pos.X && m_Pos.X + m_Bound.getWidth() > pos.X);
}

GameObjectPtr PageInstance::GetGameObjectByName( const std::string& name )
{
    for (int i = 0; i < EPAGE_LAYER_MAX; ++i)
    {
        GameObjectList_t &objects_list = m_Layers[(EPageLayer)i];

        for(GameObjectList_t::iterator i = objects_list.begin(), e = objects_list.end(); i != e; ++i)
        {
            if ((*i)->GetName() == name)
                return *i;
        };
    }

    return NULL;
}

GameObjectPtr PageInstance::GetGameObjectByHash( hash_t hash )
{
    for (int i = 0; i < EPAGE_LAYER_MAX; ++i)
    {
        GameObjectList_t &objects_list = m_Layers[(EPageLayer)i];

        for(GameObjectList_t::iterator i = objects_list.begin(), e = objects_list.end(); i != e; ++i)
        {
            if ((*i)->Hash() == hash)
                return *i;
        };
    }

    return nullptr;
}

bool_t PageInstance::AddGameObject( GameObjectPtr obj, const EPageLayer layer )
{
#ifdef DBGMODE
    GameObjectList_t &objects_list = m_Layers[layer];

    for(GameObjectList_t::iterator i = objects_list.begin(), e = objects_list.end(); i != e; ++i)
    {
        auto thisobj = *i;

        if (obj->Hash() == thisobj->Hash() ||
            obj->GetName() == thisobj->GetName())
        {
            APP_API_ASSERT("Game object already exists." && FALSE);
            LogMessage(LOG_ERR, "PageInstance::AddGameObject. Game object already exists. [" << obj->GetName() << "]");
            return FALSE;
        }
    };
#endif

    m_Layers[layer].push_back(obj);

    return TRUE;
}

GameObjectPtr PageInstance::AddGameObject( const std::string& name, const EPageLayer layer)
{
    GameObjectPtr gobj(new GameObject());

    gobj->SetName(name);
    gobj->Init();

    if (AddGameObject(gobj, layer) == FALSE)
    {
        LogMessage(LOG_ERR, "Failed to add existing object " << name);
    }

    return gobj;
}

GameObjectListIter_t PageInstance::RemoveGameObject( GameObjectPtr obj, const EPageLayer layer )
{
    GameObjectList_t& objects_list = m_Layers[layer];

    for(auto i = objects_list.begin(), e = objects_list.end(); i != e; ++i)
    {
        GameObjectPtr obj = (*i);
        if (obj->Hash() == obj->Hash()
#ifdef DBGMODE
            || obj->GetName() == obj->GetName()
#endif
            )
        {
            return objects_list.erase(i);
        }
    }

    APP_API_ASSERT("Game object is not exists." && FALSE);
    LogMessage(LOG_ERR, "PageInstance::RemoveGameObject. Game object is not exists. " << obj->GetName().c_str());

    return objects_list.end();
}

GameObjectPtr PageInstance::GetGameObjectByPoint( const core::position2df& p )
{
    for (int i = 0; i < EPAGE_LAYER_MAX; ++i)
    {
        GameObjectList_t& objects_list = m_Layers[i];

        for(auto i = objects_list.begin(), e = objects_list.end(); i != e; ++i)
        {
            if ((*i)->HitTest(p) != FALSE)
                return *i;
        }
    }

    return NULL;
}

void PageInstance::Scroll(float stepX, float stepY)
{
    m_Offset += core::position2df(stepX, stepY);

    m_DirtyPos = TRUE;
}

void PageInstance::Serialize( DynamicMemoryStream& dms )
{
    size_t layersCount = EPAGE_LAYER_MAX;
    dms.write(&layersCount);

    for (int i = 0; i < EPAGE_LAYER_MAX; ++i)
    {
        dms.write(&m_PageIndex);
        ushort_t objCount = (ushort_t)m_Layers[(EPageLayer)i].size();
        dms.write(&objCount);

        GameObjectList_t& objects_list = m_Layers[i];

        for(auto obji = objects_list.begin(), e = objects_list.end(); obji != e; ++obji)
        {
            /*uchar_t type = (*obji)->Type();
            dms.write(&type);*/

            (*obji)->Serialize(dms);
        }
    }
}

size_t PageInstance::Deserialize( MemoryStream& ms )
{
    size_t count = 0;
    size_t layersCount = 0;

    count = ms.read(&layersCount);

    if (EPAGE_LAYER_MAX != layersCount)
    {
        LogMessage(LOG_ERR, "PageInstance::Deserialize. Read file have incorrect version. Please check file format. Exist layers: " << EPAGE_LAYER_MAX << " read: " << layersCount);
        return 0;
    }

    for (int layerIndx = 0; layerIndx < EPAGE_LAYER_MAX; ++layerIndx)
    {
        count += ms.read(&m_PageIndex);
        ushort_t objCount = 0;
        count += ms.read(&objCount);

        for(ushort_t i = 0; i < objCount; ++i)
        {
            GameObjectPtr obj(new GameObject());

            count += obj->Deserialize(ms);

            AddGameObject(obj);
        }

        Init(m_PageIndex);
    }

    return count;
}

const core::rectf& PageInstance::GetBound() const
{
    return m_Bound;
}

u32 PageInstance::GetIndex() const
{
    return m_PageIndex;
}

const core::position2df& PageInstance::GetPosition() const
{
    return m_Pos;
}

void PageInstance::SetPosition( const core::position2df& pos )
{
    m_Pos = pos;
}
