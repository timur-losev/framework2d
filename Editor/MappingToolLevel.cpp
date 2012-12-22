#include "MappingToolLevel.h"
#include "CLogger.h"

MappingToolLevel::MappingToolLevel()
	: ILevel("MappingToolLevel")
	, m_Selecting(FALSE)
	, m_MapViewer(NULL)
	, m_State(MAP_STATE_IDLE)
	, m_PreviousState(MAP_STATE_IDLE)
	, m_ResizeCorner(NONE_INTERSECT)
	, m_Cursor(0)
{
	m_MapViewer = new MapViewer();
}

MappingToolLevel::~MappingToolLevel()
{

}

//*******************************************************************************
//	BASE
//
//*******************************************************************************
void MappingToolLevel::Update(float dt)
{
#ifdef USE_INVOKER
    UpdateInvoker();
#endif
	if (m_MapViewer)
	{
		m_MapViewer->Update();
	}
	
	switch(m_State)
	{
	case MAP_STATE_SELECTING_FRAME:
	{
		core::recti selection = m_Selection;
		if (m_Selection.UpperLeftCorner.X > m_Selection.LowerRightCorner.X)
		{
			selection.UpperLeftCorner.X = m_Selection.LowerRightCorner.X;
			selection.LowerRightCorner.X = m_Selection.UpperLeftCorner.X;
		}
		if (m_Selection.UpperLeftCorner.Y > m_Selection.LowerRightCorner.Y)
		{
			selection.UpperLeftCorner.Y = m_Selection.LowerRightCorner.Y;
			selection.LowerRightCorner.Y = m_Selection.UpperLeftCorner.Y;
		}
		if (m_Selecting)
		{
			GVideoDriver->draw2DRectangleOutline( selection, video::SColor(255, 255, 255, 255) );
		}
	}
	break;
	case MAP_STATE_MOVE_FRAME:
	{
		if (EMB_LEFT != m_BtnId)
		{
			u32 index = m_MapViewer->GetSelectedFrameIndex();
			if (index >= 0 && index < m_MapViewer->GetTotalFrames()) 
			{
				m_OnFrameUpdatedSignal(index, m_MapViewer->GetFramesList()->get(index));
			}
			RestoreState();
		}
	}
	break;
	case MAP_STATE_RESIZE_FRAME:
	{
		if (EMB_LEFT != m_BtnId)
		{
			u32 index = m_MapViewer->GetSelectedFrameIndex();
			if (index >= 0 && index < m_MapViewer->GetTotalFrames()) 
			{
				m_OnFrameUpdatedSignal(index, m_MapViewer->GetFramesList()->get(index));
			}
			RestoreState();
		}
	}
	break;
	};
}

bool_t MappingToolLevel::Create()
{
    return TRUE;
}

bool_t MappingToolLevel::Init()
{
    return TRUE;
}

void MappingToolLevel::Destroy()
{
    GVideoDriver->removeAllTextures();
}

void MappingToolLevel::OnMouseDown( int btn, int x, int y)
{
/*#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&MappingToolLevel::OnMouseDown, this, btn, x, y));
    }
    else
#endif*/
    {
		if (!m_MapViewer)
		{
			return;
		}

		m_MouseEvtPos.X = x;
		m_MouseEvtPos.Y = y;
		m_BtnId = btn;

		if (m_BtnId == EMB_RIGHT && m_State != MAP_STATE_MOVE_ATLAS)
		{
			ChangeState(MAP_STATE_MOVE_ATLAS);
			return;
		}
		IntersectSelection selected = m_MapViewer->IntersectWithSelectedFrame(x, y);
		if (EMB_LEFT == m_BtnId && NONE_INTERSECT != selected && BODY_INTERSECT != selected)
		{
			m_ResizeCorner = selected;
			ChangeState(MAP_STATE_RESIZE_FRAME);
		}
		else if (EMB_LEFT == m_BtnId && BODY_INTERSECT == selected)
		{
			ChangeState(MAP_STATE_MOVE_FRAME);
		}
		if (MAP_STATE_SELECTING_FRAME == m_State)
		{
			m_Selecting = TRUE;
			m_Selection.UpperLeftCorner = m_MouseEvtPos;
			m_Selection.LowerRightCorner = m_MouseEvtPos;
			return;
		}
	}
}

void MappingToolLevel::OnMouseUp( int btn, int x, int y)
{
/*#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&MappingToolLevel::OnMouseUp, this, btn, x, y));
    }
    else
#endif*/
    {
		if (!m_MapViewer)
		{
			return;
		}

		core::recti selection = m_Selection;
		if (m_Selection.UpperLeftCorner.X > m_Selection.LowerRightCorner.X)
		{
			selection.UpperLeftCorner.X = m_Selection.LowerRightCorner.X;
			selection.LowerRightCorner.X = m_Selection.UpperLeftCorner.X;
		}
		if (m_Selection.UpperLeftCorner.Y > m_Selection.LowerRightCorner.Y)
		{
			selection.UpperLeftCorner.Y = m_Selection.LowerRightCorner.Y;
			selection.LowerRightCorner.Y = m_Selection.UpperLeftCorner.Y;
		}

		if (MAP_STATE_SELECTING_FRAME == m_State)
		{
			m_Selecting = FALSE;
			if (selection.getWidth() != 0 && selection.getHeight() != 0)
			{
				core::stringc name = core::stringc(m_MapViewer->GetTotalFrames());
				FrameDef frame = FrameDef(name, (float)selection.UpperLeftCorner.X, (float)selection.UpperLeftCorner.Y, (float)selection.getWidth(), (float)selection.getHeight());

				frame.x = (frame.x - m_MapViewer->GetPosition().X) / m_MapViewer->GetScale().X;
				frame.y = (frame.y - m_MapViewer->GetPosition().Y) / m_MapViewer->GetScale().Y;
				frame.width = frame.width / m_MapViewer->GetScale().X;
				frame.height = frame.height / m_MapViewer->GetScale().Y;
				frame.textureNum = m_MapViewer->GetCurrentTexture();

				m_MapViewer->AddFrame(frame);
				m_MapViewer->SelectFrame(m_MapViewer->GetTotalFrames() - 1);

				m_OnSelectionAddedSignal(frame);
				return;
			}
		}

		if (m_MapViewer->IsShowAllSelection() && EMB_LEFT == btn)
		{
			int reselection = m_MapViewer->IntersectWithShowedFrame(x, y);
			m_MapViewer->SelectFrame(reselection);
		}

		m_MouseEvtPos.X = x;
		m_MouseEvtPos.Y = y;
		m_BtnId = EMB_NONE;
	}
}

void MappingToolLevel::OnMouseMove(int x, int y)
{
/*#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&MappingToolLevel::OnMouseMove, this, x, y));
    }
    else
#endif*/
    {
		if (!m_MapViewer)
		{
			return;
		}

		int deltaX = x - m_MouseMovePos.X;
		int deltaY = y - m_MouseMovePos.Y;
		m_MouseMovePos.X = x;
		m_MouseMovePos.Y = y;

		if (m_Selecting)
		{
			if (MAP_STATE_SELECTING_FRAME == m_State)
			{
				m_Selection.LowerRightCorner = m_MouseMovePos;
			}
		}
		if (MAP_STATE_MOVE_FRAME == m_State)
		{
			if (EMB_LEFT == m_BtnId)
			{
				m_MapViewer->UpdateSelectedPosition(deltaX, deltaY);
			}
		}
		else if (MAP_STATE_RESIZE_FRAME == m_State)
		{
			if (EMB_LEFT == m_BtnId)
			{
				if (TOP_LEFT_CORNER == m_ResizeCorner)
				{
					m_MapViewer->UpdateSelectedPosition(deltaX, deltaY);
					m_MapViewer->UpdateSelectedSize(-deltaX, -deltaY);
				}
				else if (TOP_CENTER_CORNER == m_ResizeCorner)
				{
					m_MapViewer->UpdateSelectedPosition(0, deltaY);
					m_MapViewer->UpdateSelectedSize(0, -deltaY);
				}
				else if (TOP_RIGHT_CORNER == m_ResizeCorner)
				{
					m_MapViewer->UpdateSelectedPosition(0, deltaY);
					m_MapViewer->UpdateSelectedSize(deltaX, -deltaY);
				}
				else if (RIGHT_CENTER_CORNER == m_ResizeCorner)
				{
					m_MapViewer->UpdateSelectedSize(deltaX, 0);
				}
				else if (BOTTOM_RIGHT_CORNER == m_ResizeCorner)
				{
					m_MapViewer->UpdateSelectedSize(deltaX, deltaY);
				}
				else if (BOTTOM_CENTER_CORNER == m_ResizeCorner)
				{
					m_MapViewer->UpdateSelectedSize(0, deltaY);
				}
				else if (BOTTOM_LEFT_CORNER == m_ResizeCorner)
				{
					m_MapViewer->UpdateSelectedPosition(deltaX, 0);
					m_MapViewer->UpdateSelectedSize(-deltaX, deltaY);
				}
				else if (LEFT_CENTER_CORNER == m_ResizeCorner)
				{
					m_MapViewer->UpdateSelectedPosition(deltaX, 0);
					m_MapViewer->UpdateSelectedSize(-deltaX, 0);
				}
			}
		}
		else if (MAP_STATE_MOVE_ATLAS == m_State)
		{
			if (EMB_RIGHT == m_BtnId)
			{
				m_MapViewer->SetPosition(core::position2df(m_MapViewer->GetPosition().X + deltaX, m_MapViewer->GetPosition().Y + deltaY));
			}
			else
			{
				RestoreState();
			}
		}
		else 
		{
			int reselection = m_MapViewer->IntersectWithShowedFrame(x, y);
			IntersectSelection selected = m_MapViewer->IntersectWithSelectedFrame(x, y);
			if (BODY_INTERSECT == selected)
			{
				ChangeCursorByState(MAP_STATE_MOVE_FRAME);
			}
			else if (NONE_INTERSECT != selected)
			{
				ChangeCursorByState(MAP_STATE_RESIZE_FRAME);
			}
			else 
			{
				if (reselection >= 0)
				{
					m_OnChangeCursorSignal(3);	// Cursor hand
				}
				else
				{
					ChangeCursorByState(m_State);
				}
			}
		}
	}
}

void MappingToolLevel::OnMouseWheel(int delta, int direction, int x, int y)
{
	if (m_MapViewer)
	{
		if (m_MapViewer->IntersectWithPreview(x, y))
		{
			m_OnPreviewMouseWheelSignal(delta, direction, x, y);
		}
	}
}


//*******************************************************************************
//	
//
//*******************************************************************************
void MappingToolLevel::SetPreviewDimesion( const core::position2df previewPos, const core::vector2di previewSize )
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&MappingToolLevel::SetPreviewDimesion, this, previewPos, previewSize));
    }
    else
#endif
    {
		m_MapViewer->Init(previewPos, previewSize);
    }
}

void MappingToolLevel::LoadImage( const core::stringc& path )
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&MappingToolLevel::LoadImage, this, path));
    }
    else
#endif
    {
		m_MapViewer->LoadTexture(path);
		m_MapViewer->Centering();
    }
}

void MappingToolLevel::LoadMapFile( const core::stringc& path )
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&MappingToolLevel::LoadMapFile, this, path));
    }
    else
#endif
    {
		m_MapViewer->Load(path);
		m_MapViewer->Centering();
    }
}

void MappingToolLevel::ClearFrames()
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&MappingToolLevel::ClearFrames, this));
    }
    else
#endif
    {
        
    }
}

void MappingToolLevel::ChangeName( int ind, const core::stringc& name )
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&MappingToolLevel::ChangeName, this, ind, name));
    }
    else
#endif
    {
        
    }
}

void MappingToolLevel::ChangeSelectedFrame(int index)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&MappingToolLevel::ChangeSelectedFrame, this, index));
    }
    else
#endif
    {
        if (m_MapViewer)
		{
			m_MapViewer->SelectFrame(index);
		}
    }
}

void MappingToolLevel::SetMapViewerScale(float value, int x, int y)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&MappingToolLevel::SetMapViewerScale, this, value, x, y));
    }
    else
#endif
	{
		if (m_MapViewer)
		{
			m_MapViewer->SetScaleByPoint(value, x, y);
		}
	}
}

void MappingToolLevel::SetOperation(MapStates state)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&MappingToolLevel::SetOperation, this, state));
    }
    else
#endif
	{
		ChangeState(state);
	}
}

void MappingToolLevel::ShowHideAllSelections()
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&MappingToolLevel::ShowHideAllSelections, this));
    }
    else
#endif
	{
		if (m_MapViewer)
		{
			m_MapViewer->ShowHideSelections();
		}
	}
}

void MappingToolLevel::ChangeCursorByState(MapStates state)
{
	switch(state)
	{
	case MAP_STATE_IDLE:
		m_OnChangeCursorSignal(0);
		break;
	case MAP_STATE_SELECTING_FRAME:
		m_OnChangeCursorSignal(1);
		break;
	case MAP_STATE_MOVE_FRAME:
		m_OnChangeCursorSignal(2);
		break;
	case MAP_STATE_MOVE_ATLAS:
		m_OnChangeCursorSignal(3);
		break;
	case MAP_STATE_RESIZE_FRAME:
		m_OnChangeCursorSignal(3);
		break;
	};
}

void MappingToolLevel::ChangeState(MapStates state)
{
	if (state != m_PreviousState && state != m_State)
	{
		m_PreviousState = m_State;
	}
	m_State = state;
	ChangeCursorByState(m_State);
}

void MappingToolLevel::RestoreState()
{
	m_State = m_PreviousState;
	ChangeCursorByState(m_State);
}

void MappingToolLevel::ChangeCurrentTexture(int index)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&MappingToolLevel::ChangeCurrentTexture, this, index));
    }
    else
#endif
	{
		if (m_MapViewer)
		{
			m_MapViewer->SetCurrentTexture(index);
			m_MapViewer->Centering();
		}
	}
}

void MappingToolLevel::RemoveFrame(int index)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&MappingToolLevel::RemoveFrame, this, index));
    }
    else
#endif
	{
		if (m_MapViewer)
		{
			m_MapViewer->RemoveFrame(index);
		}
	}
}


void MappingToolLevel::RemoveTexture(int index)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&MappingToolLevel::RemoveTexture, this, index));
    }
    else
#endif
	{
		if (m_MapViewer)
		{
			m_MapViewer->RemoveTexture(index);
			m_MapViewer->Centering();
		}
	}
}

//*******************************************************************************
//	SIGNALS
//
//*******************************************************************************
boost::signals::connection MappingToolLevel::AttachOnSelectionAddedSignal( const OnSelectionAddedSignal::slot_type& slot )
{
    return m_OnSelectionAddedSignal.connect(slot);
}

boost::signals::connection MappingToolLevel::AttachOnFrameBarMouseWheelSignal(const OnMouseWheelSignal::slot_type& slot)
{
	return m_OnPreviewMouseWheelSignal.connect(slot);
}

boost::signals::connection MappingToolLevel::AttachOnChangeCursorSignal(const OnChangeCursorSignal::slot_type &slot)
{
	return m_OnChangeCursorSignal.connect(slot);
}

boost::signals::connection MappingToolLevel::AttachOnFrameUpdatedSignal(const OnFrameUpdatedSignal::slot_type &slot)
{
	return m_OnFrameUpdatedSignal.connect(slot);
}