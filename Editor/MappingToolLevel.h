#ifndef MappingToolLevel_h__
#define MappingToolLevel_h__

#include "EdPrec.h"
#include "EdCommon.h"

#include "ILevel.h"
#include "MapViewer.h"




enum MapStates
{
	MAP_STATE_IDLE = 0,
	MAP_STATE_SELECTING_FRAME,
	MAP_STATE_MOVE_FRAME,
	MAP_STATE_MOVE_ATLAS,
	MAP_STATE_RESIZE_FRAME
};

class MappingToolLevel: public ILevel
{
	//*******************************************************************************
	//	SIGNALS
	//
	//*******************************************************************************
private:
    typedef boost::signal<void (const FrameDef& frame)> OnSelectionAddedSignal;
    OnSelectionAddedSignal        m_OnSelectionAddedSignal;

	typedef boost::signal<void (int, int, int, int) > OnMouseWheelSignal; //delta, direction rotation, x, y
	OnMouseWheelSignal			 m_OnPreviewMouseWheelSignal;

	typedef boost::signal<void (int) > OnChangeCursorSignal;
	OnChangeCursorSignal		 m_OnChangeCursorSignal;

	typedef boost::signal<void (int index, const FrameDef& frame)> OnFrameUpdatedSignal;
    OnFrameUpdatedSignal         m_OnFrameUpdatedSignal;
public:
    //Model events
    boost::signals::connection AttachOnSelectionAddedSignal(const OnSelectionAddedSignal::slot_type& slot);
	boost::signals::connection AttachOnFrameBarMouseWheelSignal(const OnMouseWheelSignal::slot_type& slot);
	boost::signals::connection AttachOnChangeCursorSignal(const OnChangeCursorSignal::slot_type& slot);
	boost::signals::connection AttachOnFrameUpdatedSignal(const OnFrameUpdatedSignal::slot_type& slot);

	//*******************************************************************************
	//	
	//
	//*******************************************************************************
protected:
    core::position2di       m_MouseEvtPos, m_MouseMovePos;
    int                     m_BtnId;

	MapViewer*				m_MapViewer;
	MapStates				m_State;
	MapStates				m_PreviousState;
	IntersectSelection		m_ResizeCorner;

	bool_t                  m_Selecting;
    core::recti             m_Selection;
	int						m_Cursor;

public:

    MappingToolLevel();
    virtual ~MappingToolLevel();

	//*******************************************************************************
	//	BASE
	//
	//*******************************************************************************
    virtual void            Update(float dt);
    virtual bool_t          Create();
    virtual bool_t          Init();
    virtual void            Destroy();

	//Mouse events
    void                    OnMouseDown(int, int, int);
    void                    OnMouseUp(int, int, int);
    void                    OnMouseMove(int, int);
	void                    OnMouseWheel(int delta, int direction, int x, int y);
	void					OnMouseLostFocus();

	//*******************************************************************************
	//	
	//
	//*******************************************************************************
	void					SetPreviewDimesion( const core::position2df previewPos, 
												const core::vector2di previewSize );
    void                    LoadImage (const core::stringc& path);
	void					LoadMapFile( const core::stringc& path );
    void                    ClearFrames();
    void                    ChangeSelectedFrame(int index);
    void                    ChangeName(int index, const core::stringc& name);

	void					SetMapViewerScale(float value, int x, int y);
	void					SetOperation(MapStates operation);
	void					ShowHideAllSelections();
	void					ChangeCursorByState(MapStates state);
	void					ChangeState(MapStates state);
	void					RestoreState();
	void					ChangeCurrentTexture(int index);
	void					RemoveFrame(int index);
	void					RemoveTexture(int index);
};

#endif // MappingToolLevel_h__
