#ifndef MappingToolLevel_h__
#    define MappingToolLevel_h__

#    include "ILevel.h"
#    include "MapViewer.h"

class MappingToolLevel : public ILevel, public Common::Signaling
{
public:

    enum E_SIGNALS
    {
        ES_ON_SELECTION_ADDED_SIGNAL,
        ES_ON_MOUSE_WHEEL_SIGNAL,
        ES_ON_CHANGE_CURSOR_SIGNAL,
        ES_ON_SPRITE_DATA_UPDATED_SIGNAL
    };

protected:

    enum MapStates
    {
        MAP_STATE_IDLE = 0,
        MAP_STATE_SELECTING_FRAME,
        MAP_STATE_MOVE_FRAME,
        MAP_STATE_MOVE_ATLAS,
        MAP_STATE_RESIZE_FRAME
    } ;

    bool_t                  m_Selecting;
    MapViewer*              m_MapViewer;
    MapStates               m_State;
    MapStates               m_PreviousState;
    core::position2di       m_MouseEvtPos, m_MouseMovePos;
    int                     m_BtnId;
    MapViewer::IntersectSelection   m_ResizeCorner;

    core::recti             m_Selection;
    int                     m_Cursor;
    DriverPtr               m_Driver;

public:

    MappingToolLevel();
    virtual ~MappingToolLevel();

    virtual void Update(float dt, const RenderContext& driver);
    virtual bool_t          Create();
    virtual void            Init();
    virtual void            Destroy();

    //Mouse events
    void                    OnMouseDown(int, int, int);
    void                    OnMouseUp(int, int, int);
    void                    OnMouseMove(int, int);
    void                    OnMouseWheel(int delta, int direction, int x, int y);
    void                    OnMouseLostFocus();

    void                    SetPreviewDimesion( const core::position2df previewPos,
                                                                const core::vector2di previewSize );
    void                    LoadImage (const std::string& path);
    void                    LoadMapFile( std::string path );
    void                    ClearFrames();
    void                    ChangeSelectedFrame(int index);
    void                    ChangeName(int index, const std::string& name);

    void                    SetMapViewerScale(float value, int x, int y);
    void                    SetOperation(MapStates operation);
    void                    ShowHideAllSelections(bool isShow);
    void                    ChangeCursorByState(MapStates state);
    void                    ChangeState(MapStates state);
    void                    RestoreState();
    void                    ChangeCurrentTexture(int index);
    void                    RemoveFrame(int index);
    void                    RemoveTexture(int index);
	void					ChangeFrameProperties(unsigned int index, unsigned int prop, const std::string& value, bool& validation);

    virtual const char*     DebugName() const ;/* = 0 */
} ;

#endif // MappingToolLevel_h__
