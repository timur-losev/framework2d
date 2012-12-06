#include "EdPrec.h"

#include "Page.h"
#include "StaticGameObject.h"
#include "AnimatedGameObject.h"

core::dimension2df	CPage::PageSize = core::dimension2df(960.f, 480.f);
float				CPage::BackgroundLayerSpeed = 2.f;
core::position2df	CPage::MainLayerSpeed		= core::position2df(5.f, 5.f);
float				CPage::ForegroundLayerSpeed = 7.f;

CPage::CPage()
	: m_Index(PE_UINT_MAX)
	, m_DirtyPos(FALSE)
{
}

CPage::~CPage()
{
	Destroy();
}

void CPage::Update(float dt, DriverPtr driver)
{
#ifdef USE_INVOKER
    UpdateInvoker();
#endif

	for (int i = 0; i < EPAGE_LAYER_MAX; ++i)
	{
		GameObjectList_t& objects_list = m_Layers[(ePageLayer)i];

		for(auto& obj : objects_list)
		{
			if (m_DirtyPos)
			{
				obj->Offset() += m_Offset;
			}
			obj->Update(dt, driver);
		}
	}

	if (m_DirtyPos)
	{
		m_Pos += m_Offset;
		m_DirtyPos = FALSE;
		m_Offset = core::position2df(0, 0);
	}
}

void CPage::Destroy()
{
	/*for (int i = 0; i < EPAGE_LAYER_MAX; ++i)
	{
		GameObjectList_t& objects_list = m_Layers[(ePageLayer)i];

		for(auto obji = objects_list.begin(),
            auto obje = objects_list.end(); obji != obje; ++obji)
		{
			APP_API_DEL(*obji);
		}

		m_Layers[(ePageLayer)i].clear();
	}*/
}

bool_t CPage::Init(size_t index)
{
    m_Index = index;
    m_Pos.Y = 0;
    m_Pos.X = index * PageSize.Width;
    m_Bound = core::rectf(m_Pos, PageSize);

    return TRUE;
}

const GameObjectList_t& CPage::GetObjects( const ePageLayer layer ) const
{
	return m_Layers[layer];
}

GameObjectList_t& CPage:: GetObjects(const ePageLayer layer)
{
    return m_Layers[layer];
}

bool_t CPage::HitTest( const core::position2df& pos )
{
	return (m_Pos.X <= pos.X && m_Pos.X + m_Bound.getWidth() > pos.X);
}

GameObjectPtr CPage::GetGameObjectByName( const std::string& name )
{
	for (int i = 0; i < EPAGE_LAYER_MAX; ++i)
	{
        GameObjectList_t &object_list = m_Layers[(ePageLayer)i];

		for(auto& obj: object_list)
        {
            if (obj->Name() == name)
                return obj;
        };
	}

    return NULL;
}

GameObjectPtr CPage::GetGameObjectByHash( hash_t hash )
{
	for (int i = 0; i < EPAGE_LAYER_MAX; ++i)
	{
		GameObjectList_t &object_list = m_Layers[(ePageLayer)i];

        for(auto& obj : object_list)
        {
            if (obj->Hash() == hash)
                return obj;
        }
	}

    return NULL;
}

bool_t CPage::AddGameObject( GameObjectPtr obj, const ePageLayer layer )
{
#ifdef DBGMODE
	GameObjectList_t &object_list = m_Layers[layer];

    for(auto& thisobj : object_list)
    {
        if (obj->Hash() == thisobj->Hash() || obj->Name() == thisobj->Name())
        {
            APP_API_ASSERT("Game object already exists." && FALSE);
            LogMessage(LOG_ERR, "CPage::AddGameObject. Game object already exists. [" << obj->Name() << "]");
            return FALSE;
        }
    };
#endif

#ifdef USE_INVOKER
    if (!obj->IsInvokerCreated())
        obj->CreateInvoker(Thread());
#endif

	m_Layers[layer].push_back(obj);

	return TRUE;
}

GameObjectPtr CPage::AddGameObject( const std::string& name, GameObject::EType type, const ePageLayer layer)
{
    GameObjectPtr gobj;

    switch(type)
    {
    case GameObject::ET_NONE: gobj.reset(new GameObject());
        break;
    case GameObject::ET_STATIC: gobj.reset(new StaticGameObject());
        break;
    case GameObject::ET_ANIMATED: gobj.reset(new AnimatedGameObject());
        break;
    }

    gobj->Name(name);
    gobj->Hash(); //Calc hash here

    if (AddGameObject(gobj, layer) == FALSE)
    {
        LogMessage(LOG_ERR, "Failed to add existing object " << name);
    }

    return gobj;
}

GameObjectListIter_t CPage::RemoveGameObject( GameObjectPtr obj, const ePageLayer layer )
{
	GameObjectList_t& objects_list = m_Layers[layer];

	for(auto i = objects_list.begin(), e = objects_list.end(); i != e; ++i)
	{
        GameObjectPtr obj = (*i);
		if (obj->Hash() == obj->Hash()
#ifdef DBGMODE
			|| obj->Name() == obj->Name()
#endif
			)
		{
			return objects_list.erase(i);
		}
	}

	APP_API_ASSERT("Game object is not exists." && FALSE);
	LogMessage(LOG_ERR, "CPage::RemoveGameObject. Game object is not exists. " << obj->Name().c_str());

	return objects_list.end();
}

GameObjectPtr CPage::GetGameObjectByPoint( const core::position2df& p )
{
	for (int i = 0; i < EPAGE_LAYER_MAX; ++i)
	{
        GameObjectList_t& objects_list = m_Layers[i];

		for(auto& obj : objects_list)
		{
			if (obj->HitTest(p) != FALSE)
				return obj;
		}
	}

    return NULL;
}

void CPage::Scroll(float stepX, float stepY)
{
	m_Offset += core::position2df(stepX, stepY);

	m_DirtyPos = TRUE;
}

void CPage::Serialize( DynamicMemoryStream& dms )
{
	size_t layersCount = EPAGE_LAYER_MAX;
	dms.write(&layersCount);

	for (int i = 0; i < EPAGE_LAYER_MAX; ++i)
	{
		dms.write(&m_Index);
		ushort_t objCount = (ushort_t)m_Layers[(ePageLayer)i].size();
		dms.write(&objCount);

        GameObjectList_t& objects_list = m_Layers[i];

		for(auto obji = objects_list.begin(), e = objects_list.end(); obji != e; ++obji)
		{
			uchar_t type = (*obji)->Type();
			dms.write(&type);

			(*obji)->Serialize(dms);
		}
	}
}

size_t CPage::Deserialize( MemoryStream& ms )
{
	size_t layersCount = 0;
	ms.read(&layersCount);
	if (EPAGE_LAYER_MAX != layersCount)
	{
		LogMessage(LOG_ERR, "CPage::Deserialize. Read file have incorrect version. Please check file format. Exist layers: " << EPAGE_LAYER_MAX << " read: " << layersCount);
		return 0;
	}

	size_t count = 0;
	for (int layerIndx = 0; layerIndx < EPAGE_LAYER_MAX; ++layerIndx)
	{
		count += ms.read(&m_Index);
		ushort_t objCount = 0;
		count += ms.read(&objCount);

		for(ushort_t i = 0; i < objCount; ++i)
		{
			GameObjectPtr obj = NULL;
			uchar_t type = GameObject::ET_NONE;

			count += ms.read(&type);

			switch(type)
			{
			case GameObject::ET_STATIC:
				obj.reset(new StaticGameObject());
				break;

			case GameObject::ET_ANIMATED:
				//TODO
				break;

			default:
				APP_API_ASSERT(FALSE && "Game object deserialization failed.");
				return 0;
				break;
			}

	#ifdef USE_INVOKER
			obj->CreateInvoker(Thread());
	#endif
			count += obj->Deserialize(ms);

			AddGameObject(obj);
		}

		Init(m_Index);
	}

	return count;
}
