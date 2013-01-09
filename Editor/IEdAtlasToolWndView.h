#ifndef IEdAtlasToolWndView_h__
#    define IEdAtlasToolWndView_h__

#    include "EdCommon.h"
#    include "Sprite.h"
#    include "Signaling.h"

class IEdAtlasToolWndView : public Signaling
{
public:
    typedef boost::shared_ptr<IEdAtlasToolWndView> Ptr;

    enum ESignals
    {
        ES_ON_SHOW,
        ES_ON_BUTTON_CLICKED,
        ES_ON_ZOOM_SCROLLED,
        ES_ON_OPEN_FILE,
        ES_ON_PLAY_STOP_ANIM,
        ES_ON_BUTTON_SCROLL,
        ES_ON_ANIMATON_SELECTED,
        ES_ON_FRAME_SELECTED,
        ES_ON_BUTTON_REMOVE_ANIMATION,
        ES_ON_BUTTON_REMOVE_FRAME,
        ES_ON_CHANGE_ANIMATION_DURATION,
        ES_ON_SAVE_FILE,
        ES_ON_RESIZE,
        ES_ON_CHANGE_FRAME_OFFSET
    } ;

public:

    virtual void  PushLevelManager(CLevelManager* lmgr) = 0;
    virtual void  RefreshAnimationList(SpriteAnimationsList& animList) = 0;
    virtual void  RefreshFramesList(SpriteFramesListPtr framesList, core::array<int> indexes) = 0;
    virtual void  SelectAnimation(u32 animation) = 0;
    virtual void  SelectFrame(u32 frameIndx, const FrameDef& frame) = 0;
    virtual void  MouseWheelZoom(int direction, int x, int y) = 0;
    virtual void  AttachOnMouseEvents(AtlasToolLevel* lvl) = 0;
    virtual const core::position2df GetAnimViewerPos() = 0;
    virtual const core::vector2di GetAnimViewerSize() = 0;
    virtual const core::position2df GetFramesBarPos() = 0;
    virtual const core::vector2di GetFramesBarSize() = 0;
    virtual void  ChangeCursor(int cursor) = 0;
} ;

#endif // IEdAtlasToolWndView_h__
