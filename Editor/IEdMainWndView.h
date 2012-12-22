/*
 * File:   IEdMainWndView.h
 * Author: void
 *
 * Created on February 6, 2012, 1:26 AM
 */

#ifndef IEDMAINWNDVIEW_H
#    define	IEDMAINWNDVIEW_H

#include "EdCommon.h"
#include "GameObject.h"
#include "SpriteDefs.h"
#include "Signaling.h"

class IEdMainWndView: public Signaling 
{
public:

    enum EPropertiesTags
    {
        EPT_UNSET = 0,
        EPT_POSITION,
        EPT_ROTATION,
        EPT_SCALE,
        EPT_NAME,

        EPT_FORCE_32BIT = 0x7FFFFFFF //do not use =)
    };

    enum ESignals
    {
        ES_ON_NEW_LEVEL_SELECTED,
        ES_ON_NEW_PAGE_SELECTED,
        ES_ON_SAVE_LEVEL_SELECTED,
        ES_ON_LOAD_LEVEL_SELECTED,
        ES_ON_EXIT_SELECTED,
        ES_ON_ATLAS_TOOL_SELECTED,
        ES_ON_MAPPING_SELECTED,
        ES_ON_LOAD_MAPPING_FILE,
        ES_ON_TREE_ITEM_SELECTED,
        ES_ON_ADD_NEW_STATIC_OBJECT,
        ES_ON_ADD_NEW_ANIMATED_OBJECT,
        ES_ON_GAME_OBJECT_SELECTED,
        ES_ON_GAME_OBJECT_PROPERTY_SELECTED
    };

public:
    typedef boost::shared_ptr<IEdMainWndView> Ptr;

    typedef core::map<core::stringc, SpriteFramesListPtr>          ConstructNodes_t;
    typedef core::map<core::stringc, GameObject::Ptr>              ElementsNodes_t;
    typedef core::array<boost::signals::connection>                MultipleConnections_t;
public:

    virtual void					PushLevelManager(CLevelManager* lmgr)					= 0;
    virtual MultipleConnections_t	AttachOnMouseEvents(EditablePagedLevel* lvl)			= 0;
    virtual MultipleConnections_t	AttachOnKeyEvents(EditablePagedLevel* lvl)				= 0;
    virtual void					RefreshConstructNodes(const ConstructNodes_t& nodes)	= 0;
    virtual void					RefreshElementsNodes(const ElementsNodes_t& nodes)		= 0;
    virtual void					ReadPropertiesFromObject(GameObject::Ptr obj)			= 0;
    virtual void					MarkSelectedObjectInElementsTree(GameObject::Ptr obj)	= 0;
};
#endif	/* IEDMAINWNDVIEW_H */

