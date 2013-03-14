#include "EdPrec.h"
#include "MappingToolLevel.h"

MappingToolLevel::MappingToolLevel()
    : ILevel("MappingToolLevel")
    , m_Selecting(FALSE)
    , m_MapViewer(nullptr)
    , m_State(MAP_STATE_SELECTING_FRAME)
    , m_PreviousState(MAP_STATE_IDLE)
    , m_ResizeCorner(MapViewer::NONE_INTERSECT)
    , m_Cursor(0)
    , m_Driver(nullptr)
{
	m_MapViewer = APP_API_NEW(MapViewer);
}

MappingToolLevel::~MappingToolLevel()
{
	Destroy();
}

//*******************************************************************************
//	BASE
//
//*******************************************************************************
void MappingToolLevel::Update( float dt, const RenderContext& context)
{
    m_Driver = context.Driver;
#ifdef USE_INVOKER
    UpdateInvoker();
#endif
    if (m_MapViewer)
    {
        m_MapViewer->Update(context);
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
                m_Driver->draw2DRectangleOutline( selection, video::SColor(255, 255, 255, 255) );
            }
        }

        break;
    case MAP_STATE_MOVE_FRAME:
    case MAP_STATE_RESIZE_FRAME:
        {
            if (EMB_LEFT != m_BtnId)
            {
                CallBack<const SpriteInstance*>(ES_ON_SPRITE_DATA_UPDATED_SIGNAL, m_MapViewer);
                RestoreState();
            }
        }
        break;

    case MAP_STATE_IDLE:
        /*idle*/
        break;

    default:
        //APP_API_ASSERT(FALSE);
		break;

    };
}

bool_t MappingToolLevel::Create()
{
    return TRUE;
}

void MappingToolLevel::Init()
{

}

void MappingToolLevel::Destroy()
{
	APP_API_DEL(m_MapViewer);
    //m_Driver->removeAllTextures();
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
        MapViewer::IntersectSelection selected = m_MapViewer->IntersectWithSelectedFrame(x, y);
        if (EMB_LEFT == m_BtnId &&
            MapViewer::NONE_INTERSECT != selected &&
            MapViewer::BODY_INTERSECT != selected)
        {
            m_ResizeCorner = selected;
            ChangeState(MAP_STATE_RESIZE_FRAME);
        }
        else if (EMB_LEFT == m_BtnId && MapViewer::BODY_INTERSECT == selected)
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
                FrameDef frame;
				if (m_MapViewer->AddFrame(selection, frame))
				{
					m_MapViewer->SelectFrame(m_MapViewer->GetTotalFrames() - 1);
					//CallBack(ES_ON_SELECTION_ADDED_SIGNAL, std::ref(frame));
					CallBack<const SpriteInstance*>(ES_ON_SPRITE_DATA_UPDATED_SIGNAL, m_MapViewer);
				}
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
				m_MapViewer->UpdateSelectedSize(deltaX, deltaY);
            }
        }
        else if (MAP_STATE_RESIZE_FRAME == m_State)
        {
            if (EMB_LEFT == m_BtnId)
            {
                if (MapViewer::TOP_LEFT_CORNER == m_ResizeCorner)
                {
                    m_MapViewer->UpdateSelectedPosition(deltaX, deltaY);
                }
                else if (MapViewer::TOP_CENTER_CORNER == m_ResizeCorner)
                {
                    m_MapViewer->UpdateSelectedPosition(0, deltaY);
                }
                else if (MapViewer::TOP_RIGHT_CORNER == m_ResizeCorner)
                {
                    m_MapViewer->UpdateSelectedPosition(0, deltaY);
                    m_MapViewer->UpdateSelectedSize(deltaX, 0);
                }
                else if (MapViewer::RIGHT_CENTER_CORNER == m_ResizeCorner)
                {
                    m_MapViewer->UpdateSelectedSize(deltaX, 0);
                }
                else if (MapViewer::BOTTOM_RIGHT_CORNER == m_ResizeCorner)
                {
                    m_MapViewer->UpdateSelectedSize(deltaX, deltaY);
                }
                else if (MapViewer::BOTTOM_CENTER_CORNER == m_ResizeCorner)
                {
                    m_MapViewer->UpdateSelectedSize(0, deltaY);
                }
                else if (MapViewer::BOTTOM_LEFT_CORNER == m_ResizeCorner)
                {
                    m_MapViewer->UpdateSelectedPosition(deltaX, 0);
                    m_MapViewer->UpdateSelectedSize(0, deltaY);
                }
                else if (MapViewer::LEFT_CENTER_CORNER == m_ResizeCorner)
                {
                    m_MapViewer->UpdateSelectedPosition(deltaX, 0);
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
            MapViewer::IntersectSelection selected = m_MapViewer->IntersectWithSelectedFrame(x, y);
            if (MapViewer::BODY_INTERSECT == selected)
            {
                ChangeCursorByState(MAP_STATE_MOVE_FRAME);
            }
            else if (MapViewer::NONE_INTERSECT != selected)
            {
                ChangeCursorByState(MAP_STATE_RESIZE_FRAME);
            }
            else
            {
                if (reselection >= 0)
                {
                    CallBack(ES_ON_CHANGE_CURSOR_SIGNAL, 3);
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
    /*if (m_MapViewer)
    {
        if (m_MapViewer->IntersectWithPreview(x, y))
        {
            CallBack(ES_ON_MOUSE_WHEEL_SIGNAL, delta, direction, x, y);
        }
    }*/
}

void MappingToolLevel::SetPreviewDimesion( const core::position2df previewPos, const core::vector2di previewSize )
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&MappingToolLevel::SetPreviewDimesion, this, previewPos, previewSize));
    }
    else
#endif
    {
		m_MapViewer->SetPreviewDimension(previewPos, previewSize);
		m_MapViewer->Centering();
    }
}

void MappingToolLevel::LoadImage( const std::string& path )
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&MappingToolLevel::LoadImage, this, path));
    }
    else
#endif
    {
        //m_MapViewer->LoadTexture(path);
        m_MapViewer->Centering();
    }
}

void MappingToolLevel::LoadMapFile( std::string path )
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&MappingToolLevel::LoadMapFile, this, path));
		return;
    }
    else
#endif
    {
        m_MapViewer->Load(path);
        m_MapViewer->Centering();

		CallBack<const SpriteInstance*>(ES_ON_SPRITE_DATA_UPDATED_SIGNAL, m_MapViewer);
    }
}

void MappingToolLevel::ClearFrames()
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&MappingToolLevel::ClearFrames, this));
    }
    else
#endif
    {

    }
}

void MappingToolLevel::ChangeName( int ind, const std::string& name )
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&MappingToolLevel::ChangeName, this, ind, name));
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
        BeginInvoke(std::bind(&MappingToolLevel::ChangeSelectedFrame, this, index));
    }
    else
#endif
    {
        if (m_MapViewer)
        {
            m_MapViewer->SelectFrame(index, true);
        }
    }
}

void MappingToolLevel::SetMapViewerScale(float value, int x, int y)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&MappingToolLevel::SetMapViewerScale, this, value, x, y));
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
        BeginInvoke(std::bind(&MappingToolLevel::SetOperation, this, state));
    }
    else
#endif
    {
        ChangeState(state);
    }
}

void MappingToolLevel::ShowHideAllSelections(bool isShow)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&MappingToolLevel::ShowHideAllSelections, this, isShow));
    }
    else
#endif
    {
        if (m_MapViewer)
        {
            m_MapViewer->ShowHideSelections(isShow);
        }
    }
}

void MappingToolLevel::ChangeCursorByState(MapStates state)
{
    switch(state)
    {
    case MAP_STATE_IDLE:
        CallBack(ES_ON_CHANGE_CURSOR_SIGNAL, 0);
        break;
    case MAP_STATE_SELECTING_FRAME:
        CallBack(ES_ON_CHANGE_CURSOR_SIGNAL, 1);
        break;
    case MAP_STATE_MOVE_FRAME:
        CallBack(ES_ON_CHANGE_CURSOR_SIGNAL, 2);
        break;
    case MAP_STATE_MOVE_ATLAS:
        CallBack(ES_ON_CHANGE_CURSOR_SIGNAL, 3);
        break;
    case MAP_STATE_RESIZE_FRAME:
        CallBack(ES_ON_CHANGE_CURSOR_SIGNAL, 3);
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
        BeginInvoke(std::bind(&MappingToolLevel::ChangeCurrentTexture, this, index));
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
        BeginInvoke(std::bind(&MappingToolLevel::RemoveFrame, this, index));
    }
    else
#endif
    {
        if (m_MapViewer)
        {
            m_MapViewer->RemoveFrame(index);

			CallBack<const SpriteInstance*>(ES_ON_SPRITE_DATA_UPDATED_SIGNAL, m_MapViewer);
        }
    }
}


void MappingToolLevel::RemoveTexture(int index)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&MappingToolLevel::RemoveTexture, this, index));
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

void MappingToolLevel::ChangeFrameProperties(unsigned int index, unsigned int prop, const std::string& value, bool& validation)
{
	validation = false;

	if (m_MapViewer)
    {
		validation = m_MapViewer->ChangeFrameProperties(index, prop, value);
    }
}

const char* MappingToolLevel::DebugName() const
{
    return "MappingToolLevel";
}
