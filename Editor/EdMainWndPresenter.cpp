/*
* File:   EdMainWndPresenter.cpp
* Author: void
*
* Created on February 6, 2012, 12:21 AM
*/

#include "EdMainWndPresenter.h"
#include "EdViewHolder.h"
#include "EdPresenterHolder.h"

#include "EditablePagedLevel.h"
#include "Page.h"
#include "LevelManager.h"
#include "AssetsManager.h"
#include "LevelFile.h"

#include <boost/lexical_cast.hpp>
#include "CLogger.h"

EdMainWndPresenter::EdMainWndPresenter()
	: m_Level(NULL)
	, m_NowSelectedGameObject(NULL)
{
    m_View = EdViewHolder::getRef().MainWindow();
    UpdateView();
    AttachViewSlots();

    m_LevelManager = new CLevelManager();

    m_View->PushLevelManager(m_LevelManager);
}

void EdMainWndPresenter::UpdateView()
{
}

void EdMainWndPresenter::AttachViewSlots()
{
    m_View->AttachOn(IEdMainWndView::ES_ON_NEW_LEVEL_SELECTED, boost::bind(&EdMainWndPresenter::OnNewLevelSelected, this));
    m_View->AttachOn(IEdMainWndView::ES_ON_NEW_PAGE_SELECTED, boost::bind(&EdMainWndPresenter::OnNewPageSignal, this));
    m_View->AttachOn(IEdMainWndView::ES_ON_ATLAS_TOOL_SELECTED, boost::bind(&EdMainWndPresenter::OnAtlasToolsSelected, this));
    m_View->AttachOn(IEdMainWndView::ES_ON_MAPPING_SELECTED, boost::bind(&EdMainWndPresenter::OnMappingToolSelected, this));
    m_View->AttachOn(IEdMainWndView::ES_ON_ADD_NEW_STATIC_OBJECT, boost::bind(&EdMainWndPresenter::OnNewStaticObjectSelected, this));
    m_View->AttachOn(IEdMainWndView::ES_ON_ADD_NEW_ANIMATED_OBJECT, boost::bind(&EdMainWndPresenter::OnNewAnimatedObjectSelected, this));


    m_View->AttachOn<io::path>(IEdMainWndView::ES_ON_LOAD_MAPPING_FILE, boost::bind(&EdMainWndPresenter::OnLoadMappingFile, this, _1));
    m_View->AttachOn<core::stringc, core::stringc>(IEdMainWndView::ES_ON_TREE_ITEM_SELECTED, boost::bind(&EdMainWndPresenter::OnTreeItemSelected, this, _1, _2));
    m_View->AttachOn<core::stringc>(IEdMainWndView::ES_ON_GAME_OBJECT_SELECTED, boost::bind(&EdMainWndPresenter::OnGameObjectSelected, this, _1));
    m_View->AttachOn<core::stringc>(IEdMainWndView::ES_ON_SAVE_LEVEL_SELECTED, boost::bind(&EdMainWndPresenter::OnSaveLevelFile, this, _1));
    m_View->AttachOn<core::stringc>(IEdMainWndView::ES_ON_LOAD_LEVEL_SELECTED, boost::bind(&EdMainWndPresenter::OnLoadLevelFile, this, _1));
    m_View->AttachOn<IEdMainWndView::EPropertiesTags>(IEdMainWndView::ES_ON_GAME_OBJECT_PROPERTY_SELECTED, boost::bind(&EdMainWndPresenter::OnGameObjectPropertySelectedSignal, this, _1));
}

EdMainWndPresenter::~EdMainWndPresenter()
{
}

void EdMainWndPresenter::OnNewLevelSelected()
{
    if(!m_SetNameForNewLevelConnection.connected())
        m_SetNameForNewLevelConnection = EdViewHolder::getRef().SetNameForSelectionDialog()->AttachOnOkSignal(boost::bind(&EdMainWndPresenter::OnNameForNewLevelSelected, this, _1));

    EdPresenterHolder::getRef().ShowSetNameForSelectionDialog();
}

void EdMainWndPresenter::OnNameForNewLevelSelected( const core::stringc& name )
{
    m_SetNameForNewLevelConnection.disconnect();

    if (name.empty())
        return;

    if (m_Level)
        DestroyCurrentLevel();

    m_Level = new EditablePagedLevel(name);

    m_Level->LockUnlock(true); //to prevent unnecessary updates

    m_LevelManager->AttachLevel(m_Level);
    m_Level->Init();

    m_Level->LockUnlock(false);

    AttachModelSlots();
}

void EdMainWndPresenter::OnNewPageSignal()
{
    if (!m_Level) return;

    CPage* page = new CPage();
    m_Level->AddPage(page);
}

void EdMainWndPresenter::OnAtlasToolsSelected()
{
    EdPresenterHolder::getRef().ShowAtlasToolDialog();
}

void EdMainWndPresenter::OnMappingToolSelected()
{
    EdPresenterHolder::getRef().ShowMappingToolDialog();
}

void EdMainWndPresenter::OnLoadMappingFile( const io::path& fileName )
{
    SpriteFramesListPtr			frames	= PTR_NEW(SpriteFramesList());
    SpriteTexturesNamesListPtr	names	= PTR_NEW(SpriteTexturesNamesList());
	SpriteAnimationsListPtr		anims	= PTR_NEW(SpriteAnimationsList());

    if (!AssetsManager::getRef().GetMapping(fileName, frames, anims, names))
        return;

    core::stringc key = APP_API_GET_SIMPLE_FILE_NAME(fileName.c_str());
    if (m_Frames.find(key) == NULL)
    {
        m_Frames[key] = frames;
        m_TextureNames[key] = names;
    }

    m_View->RefreshConstructNodes(m_Frames);
}

void EdMainWndPresenter::OnTreeItemSelected( const core::stringc& mpfitem,
    const core::stringc& subitem )
{
    if (!m_NowSelectedGameObject || m_NowSelectedGameObject->Type() != GameObject::ET_STATIC) return;

    const SpriteTexturesNamesListPtr& textureNames = m_TextureNames.find(mpfitem)->getValue();
    const SpriteFramesListPtr& sels = m_Frames.find(mpfitem)->getValue();
    const FrameDef* ent = NULL;
    for (uint i = 0; i < sels->size(); ++ i)
    {
        if (sels->get(i).name == subitem)
        {
            ent = &sels->get(i);
            break;
        }
    }

    APP_API_ASSERT(ent != NULL);

    m_NowSelectedGameObject->AsStaticGameObject()->AddGraphicItem(textureNames->get(0), *ent);
    m_View->RefreshElementsNodes(m_ElementsNodes);
}

void EdMainWndPresenter::OnNewStaticObjectSelected()
{
    if(!m_SetNameForNewObjectConnection.connected())
        m_SetNameForNewObjectConnection = EdViewHolder::getRef().SetNameForSelectionDialog()->AttachOnOkSignal(boost::bind(&EdMainWndPresenter::OnNameForNewObjectSelected, this, _1));

    m_ExpectedObjectType = GameObject::ET_STATIC;

    EdPresenterHolder::getRef().ShowSetNameForSelectionDialog();
}

void EdMainWndPresenter::OnNewAnimatedObjectSelected()
{
    if(!m_SetNameForNewObjectConnection.connected())
        m_SetNameForNewObjectConnection = EdViewHolder::getRef().SetNameForSelectionDialog()->AttachOnOkSignal(boost::bind(&EdMainWndPresenter::OnNameForNewObjectSelected, this, _1));

    m_ExpectedObjectType = GameObject::ET_ANIMATED;

    EdPresenterHolder::getRef().ShowSetNameForSelectionDialog();
}

void EdMainWndPresenter::OnNameForNewObjectSelected( const core::stringc& name )
{
    m_SetNameForNewObjectConnection.disconnect();

    EditablePagedLevel* current = static_cast<EditablePagedLevel*>(m_LevelManager->CurrentLevel());
    if (!current) return;
    CPage* page = current->GetEditablePage();

    if (!page) return;

    GameObject::Ptr obj = page->AddGameObject(name, m_ExpectedObjectType);

    APP_API_ASSERT(m_Frames.find(name) == 0);

    m_ElementsNodes[name] = obj;

    m_View->RefreshElementsNodes(m_ElementsNodes);
}

void EdMainWndPresenter::OnGameObjectSelected( const core::stringc& name )
{
    IEdMainWndView::ElementsNodes_t::Node* found = m_ElementsNodes.find(name);

    APP_API_ASSERT(found);

    m_NowSelectedGameObject = found->getValue();

    m_View->ReadPropertiesFromObject(m_NowSelectedGameObject);
}

void EdMainWndPresenter::OnGameObjectSelectedFromModel( GameObject::Ptr obj )
{
    m_NowSelectedGameObject = obj;
    m_View->ReadPropertiesFromObject(m_NowSelectedGameObject);
    m_View->MarkSelectedObjectInElementsTree(obj);
}

void EdMainWndPresenter::OnGameObjectPropertySelectedSignal( IEdMainWndView::EPropertiesTags tag )
{
    APP_API_ASSERT(m_NowSelectedGameObject);

    IEdSetValueView::Ptr dlg = EdViewHolder::getRef().SetValueDialog();
    dlg->Clear();

    switch(tag)
    {
    case IEdMainWndView::EPT_POSITION:
        dlg->Values(m_NowSelectedGameObject->Position().X, m_NowSelectedGameObject->Position().Y);
        break;
    case IEdMainWndView::EPT_ROTATION:
        dlg->Values(core::stringc(m_NowSelectedGameObject->Rotation()), "");
        break;
    case IEdMainWndView::EPT_SCALE:
        dlg->Values(m_NowSelectedGameObject->Scale().X, m_NowSelectedGameObject->Scale().Y);
        break;
    case IEdMainWndView::EPT_NAME:
        dlg->Values(m_NowSelectedGameObject->Name(), "");
        break;
    };

    m_NowEditableProperty = tag;

    if (!m_SetValueConnection.connected())
        m_SetValueConnection = EdViewHolder::getRef().SetValueDialog()->AttachValueChangedSignal(boost::bind(&EdMainWndPresenter::OnGameObjectPropertyValueChangedSignal, this, _1, _2));

    EdPresenterHolder::getRef().ShowSetValueDialog();
}

void EdMainWndPresenter::OnGameObjectPropertyValueChangedSignal( const core::stringc& v1, const core::stringc& v2 )
{
    APP_API_ASSERT(m_NowSelectedGameObject);

    try
    {
        switch(m_NowEditableProperty)
        {
        case IEdMainWndView::EPT_POSITION:
            {
                float X = boost::lexical_cast<float>(v1.c_str());
                float Y = boost::lexical_cast<float>(v2.c_str());

                m_NowSelectedGameObject->Position(core::position2df(X, Y));
            }
            break;
        case IEdMainWndView::EPT_ROTATION:
            {
                float R = boost::lexical_cast<float>(v1.c_str());
                m_NowSelectedGameObject->Rotation(R);
            }
            break;
        case IEdMainWndView::EPT_SCALE:
            {
                float X = boost::lexical_cast<float>(v1.c_str());
                float Y = boost::lexical_cast<float>(v2.c_str());

                m_NowSelectedGameObject->Scale(core::position2df(X, Y));
            }
            break;
        case IEdMainWndView::EPT_NAME:
            {
                if (!v1.empty())
                    m_NowSelectedGameObject->Name(v1);
            }
            break;
        };

        m_View->ReadPropertiesFromObject(m_NowSelectedGameObject);
    }
    catch(boost::bad_lexical_cast& e)
    {
        LogDebug(e.what());
    }
    
}

void EdMainWndPresenter::OnSaveLevelFile( const core::stringc& fname )
{
    if (!m_Level) return;

    LevelFile::Save(fname, m_Level);
}

void EdMainWndPresenter::OnLoadLevelFile( const core::stringc& fname )
{
    if (m_Level)
    {
        DestroyCurrentLevel();
    }

    m_Level = APP_API_NEW EditablePagedLevel("");

    m_Level->LockUnlock(TRUE);

    m_LevelManager->AttachLevel(m_Level);

    LevelFile::Load(fname, m_Level);

    Invoker::PerformCrossThreadCall(boost::bind(&EditablePagedLevel::LockUnlock, m_Level, FALSE), m_Level, TRUE);

    DeserializeInformationFromCurrentLevel();
    AttachModelSlots();
}

void EdMainWndPresenter::DetachModelSlots()
{
    size_t i = 0;
    for (; i < m_MouseConnections.size(); ++i)
    {
        m_MouseConnections[i].disconnect();
    }

    for(i = 0; i < m_KeyConnections.size(); ++i)
    {
        m_KeyConnections[i].disconnect();
    }
}

void EdMainWndPresenter::AttachModelSlots()
{
    m_KeyConnections = m_View->AttachOnKeyEvents(m_Level);
    m_MouseConnections = m_View->AttachOnMouseEvents(m_Level);
    m_Level->AttachOnGameObjectSelectedSignal(boost::bind(&EdMainWndPresenter::OnGameObjectSelectedFromModel, this, _1));
}

void EdMainWndPresenter::DeserializeInformationFromCurrentLevel()
{
    APP_API_ASSERT(m_Level);

    m_ElementsNodes.clear();

    for (size_t iPage = 0; iPage < m_Level->GetPagesCount(); ++iPage)
    {
        CPage* page = m_Level->GetPageByIndex(iPage);
        for (GameObjectListIter_t iObj = page->GetObjects().begin(), eObj = page->GetObjects().end();
            iObj != eObj; ++iObj)
        {
            GameObject::Ptr obj = *iObj;

            switch(obj->Type())
            {
            case GameObject::ET_STATIC:
                {
                    StaticGameObject::Ptr stobj = obj->AsStaticGameObject();

                    const StaticGameObject::GraphicState_t& grstate = stobj->GraphicState();

                    if (!grstate.empty())
                    {
                        //WARNING! Frame must be loaded already
                        const StaticGameObject::GraphicItem& item = grstate.front();
                        const core::stringc& origin = MEDIA_PATH + AssetsManager::getRef().GetOrigin(item.m_FrameInfo.uid);
                        OnLoadMappingFile(origin);
                    }

                    m_ElementsNodes[obj->Name()] = obj;
                }
                break;

            case GameObject::ET_ANIMATED:
                //TODO
                break;

            default:
                APP_API_ASSERT(FALSE);
            }
        }
    }

    m_View->RefreshElementsNodes(m_ElementsNodes);
}

void EdMainWndPresenter::DestroyCurrentLevel()
{
    APP_API_ASSERT(m_Level);

    DetachModelSlots();
    Invoker::PerformCrossThreadCall(boost::bind(&EditablePagedLevel::LockUnlock, m_Level, TRUE), m_Level, TRUE);
    Invoker::PerformCrossThreadCall(boost::bind(&EditablePagedLevel::Destroy, m_Level), m_Level, TRUE);

    m_LevelManager->DetatchLevel(m_Level);
    APP_API_DEL(m_Level);

    m_ElementsNodes.clear();
    m_View->RefreshElementsNodes(m_ElementsNodes);
}
