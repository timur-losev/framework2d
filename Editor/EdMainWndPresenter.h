/*
 * File:   EdMainWndPresenter.h
 * Author: void
 *
 * Created on February 6, 2012, 12:21 AM
 */

#ifndef EDMAINWNDPRESENTER_H
#    define	EDMAINWNDPRESENTER_H

#include "IEdMainWndView.h"

#include "GameObject.h"
#include "StaticGameObject.h"
#include "AnimatedGameObject.h"
#include "SpriteDefs.h"

class EdMainWndPresenter
{
private:
    IEdMainWndView::Ptr							m_View;

    CLevelManager*							    m_LevelManager;
    EditablePagedLevel*							m_Level;

    IEdMainWndView::ConstructNodes_t		    m_Frames;
    IEdMainWndView::ElementsNodes_t			    m_ElementsNodes;
    //MappingToTextureMap_t						m_MappingToTexture;
    FMap<FString, SpriteTexturesNamesListPtr>	m_TextureNames;
    
    boost::signals::connection					m_SetNameForNewObjectConnection;
    boost::signals::connection					m_SetNameForNewLevelConnection;
    boost::signals::connection					m_SetValueConnection;
    IEdMainWndView::MultipleConnections_t		m_MouseConnections;
    IEdMainWndView::MultipleConnections_t		m_KeyConnections;

    GameObject::Ptr								m_NowSelectedGameObject;
    IEdMainWndView::EPropertiesTags				m_NowEditableProperty;

    GameObject::EType							m_ExpectedObjectType;
private:
    void										OnNewLevelSelected();
    void										OnNewPageSignal();
    void									    OnAtlasToolsSelected();
    void										OnMappingToolSelected();
    void										OnLoadMappingFile(const io::path& str);
    void									    OnTreeItemSelected(const core::stringc& mpfitem, const core::stringc& subitem);
    void										OnNewStaticObjectSelected();
    void										OnNewAnimatedObjectSelected();
    void										OnNameForNewObjectSelected(const core::stringc& name);
    void										OnNameForNewLevelSelected(const core::stringc& name);
    void										OnGameObjectSelected(const core::stringc& name); //from view
    void										OnGameObjectSelectedFromModel(GameObject::Ptr obj); //from model
    void										OnGameObjectPropertySelectedSignal(IEdMainWndView::EPropertiesTags tag);
    void										OnGameObjectPropertyValueChangedSignal(const core::stringc& v1, const core::stringc& v2);
    void										OnSaveLevelFile(const core::stringc& fname);
    void										OnLoadLevelFile(const core::stringc& fname);

    void										DestroyCurrentLevel();

    void										UpdateView();
    void										AttachViewSlots();
    void										DetachModelSlots();
    void										AttachModelSlots();

    void										DeserializeInformationFromCurrentLevel();
public:
    typedef boost::shared_ptr<EdMainWndPresenter> Ptr;

    EdMainWndPresenter();
    ~EdMainWndPresenter();
} ;

#endif	/* EDMAINWNDPRESENTER_H */

