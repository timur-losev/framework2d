#ifndef IEdMappingToolWndView_h__
#define IEdMappingToolWndView_h__

#include "EdCommon.h"
#include "SpriteDefs.h"
#include "Signaling.h"

class IEdMappingToolWndView: public Signaling
{
public:
    typedef boost::shared_ptr<IEdMappingToolWndView> Ptr;

public:

    enum ESignals
    {
        ES_ON_SHOW,
        ES_ON_OPEN_IMAGE,
        ES_ON_SAVE_MAPPING_FILE,
        ES_ON_OPEN_MAPPING_FILE,
        ES_ON_CLEAR_SELECTION,
        ES_ON_SET_NAME_FOR_SELECTION,
        ES_ON_ZOOM_SCROLLED,
        ES_ON_BUTTON_ADD_FRAME,
        ES_ON_BUTTON_SHOW_HIDE_FRAMES,
        ES_ON_RESIZE,
        ES_ON_CHANGE_CURRENT_TEXTURE,
        ES_ON_REMOVE_FRAME,
        ES_ON_REMOVE_TEXTURE,
        ES_ON_CHANGE_SELECTED_FRAME
    };

    virtual void						AttachOnMouseEvents(MappingToolLevel* lvl) = 0;
    virtual void						PushLevelManager(CLevelManager* lmgr) = 0;
    virtual void                        RefreshFramesList(const SpriteFramesListPtr& frames) = 0;
	virtual void						RefreshTexturesList(const SpriteTexturesNamesListPtr& names) = 0;
	virtual void						MouseWheelZoom(int direction, int x, int y) = 0;
	virtual const core::position2df		GetMapViewerPos() = 0;
	virtual const core::vector2di		GetMapViewerSize() = 0;
	virtual int							GetSelectedFrameIndex() = 0;
	virtual void						ChangeCursor(int cursor) = 0;
};

#endif // IEdMappingToolWndView_h__
