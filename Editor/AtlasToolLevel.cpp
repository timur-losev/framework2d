#include "AtlasToolLevel.h"
#include "AppApi.h"

AtlasToolLevel::AtlasToolLevel()
	: ILevel("AtlasToolLevel")
	, m_State(ANIM_STATE_IDLE)
	, m_PreviousState(ANIM_STATE_IDLE)
{
	m_AnimViewer = new AnimViewer();
}

AtlasToolLevel::~AtlasToolLevel()
{
	APP_API_DEL(m_AnimViewer);
}

//*******************************************************************************
//	BASE
//
//*******************************************************************************
void AtlasToolLevel::Update(float dt)
{
	if (m_AnimViewer)
	{
		m_AnimViewer->Update();
	}

	UpdateInvoker();
}

bool_t AtlasToolLevel::Create()
{
    return TRUE;
}

bool_t AtlasToolLevel::Init()
{
    return TRUE;
}

void AtlasToolLevel::Destroy()
{
    
}

void AtlasToolLevel::OnMouseDown( int btn, int x, int y)
{
	if (!m_AnimViewer)
	{
		return;
	}

	m_MouseEvtPos.X = x;
	m_MouseEvtPos.Y = y;
	m_BtnId = btn;

	if (m_BtnId == EMB_RIGHT && m_State != ANIM_STATE_MOVE_ATLAS)
	{
		ChangeState(ANIM_STATE_MOVE_ATLAS);
	}
	else if (m_BtnId == EMB_LEFT && m_AnimViewer->CheckFrameViewCollision(x, y) && m_State != ANIM_STATE_MOVE_FRAME)
	{
		ChangeState(ANIM_STATE_MOVE_FRAME);
	}
}

void AtlasToolLevel::OnMouseUp( int btn, int x, int y)
{
	if (m_AnimViewer)
	{
		int frame = m_AnimViewer->CheckFrameBarCollision(x, y);
		if (frame != -1)
		{
			m_OnFrameBarSelectedSignal(frame);
		}
	}

	m_MouseEvtPos.X = x;
	m_MouseEvtPos.Y = y;
	m_BtnId = EMB_NONE;
}

void AtlasToolLevel::OnMouseMove(int x, int y)
{
	if (!m_AnimViewer)
	{
		return;
	}

	int deltaX = x - m_MouseMovePos.X;
	int deltaY = y - m_MouseMovePos.Y;
	m_MouseMovePos.X = x;
	m_MouseMovePos.Y = y;

    if (ANIM_STATE_MOVE_ATLAS == m_State)
	{
		if (EMB_RIGHT == m_BtnId)
		{
			m_AnimViewer->SetPosition(core::position2df(m_AnimViewer->GetPosition().X + deltaX, m_AnimViewer->GetPosition().Y + deltaY));
		}
		else
		{
			RestoreState();
		}
	}
	else if (ANIM_STATE_MOVE_FRAME == m_State)
	{
		if (EMB_LEFT == m_BtnId)
		{
			FrameDef frame; 
			if (m_AnimViewer->SetFrameOffset(m_AnimViewer->GetFrameOffset().X + deltaX / m_AnimViewer->GetScale().X, 
				m_AnimViewer->GetFrameOffset().Y + deltaY / m_AnimViewer->GetScale().Y, frame))
			{
				m_OnFrameUpdatedSignal(m_AnimViewer->GetCurrentFrame(), frame);
			}
		}
		else
		{
			RestoreState();
		}
	}
	else if (m_AnimViewer->CheckFrameViewCollision(x, y))
	{
		m_OnChangeCursorSignal(3);	// Cursor hand
	}
	else 
	{
		ChangeCursorByState(m_State);
	}
}

void AtlasToolLevel::OnMouseDblClick(int btn, int x, int y)
{
	if (m_AnimViewer)
	{
		int frame = m_AnimViewer->CheckFrameBarCollision(x, y);
		if (frame != -1)
		{
			m_OnFrameBarAddFrameSignal(frame);
		}
	}
}

void AtlasToolLevel::OnMouseWheel(int delta, int direction, int x, int y)
{
	if (m_AnimViewer)
	{
		if (m_AnimViewer->IntersectWithPreview(x, y))
		{
			m_OnPreviewMouseWheelSignal(delta, direction, x, y);
		}
		if (m_AnimViewer->IntersectWithFrameBar(x, y))
		{
			m_OnFrameBarMouseWheelSignal(delta, direction, x, y);
		}
	}
}

//*******************************************************************************
//	
//
//*******************************************************************************
void AtlasToolLevel::SetPreviewDimesion( const core::position2df& previewPos, 
										 const core::vector2di& previewSize, 
										 const core::position2df& framesPos, 
										 const core::vector2di& framesSize )
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&AtlasToolLevel::SetPreviewDimesion, this, previewPos, previewSize, framesPos, framesSize));
    }
    else
#endif
    {
		m_AnimViewer->Init(previewPos, previewSize, framesPos, framesSize);
    }
}

void AtlasToolLevel::LoadAnimation( const io::path& path )
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&AtlasToolLevel::LoadAnimation, this, path));
    }
    else
#endif
    {
		m_AnimViewer->Load(path);
		m_OnAnimationLoadedSignal(m_AnimViewer->GetAnimationsList(), m_AnimViewer->GetFramesList(), m_AnimViewer->GetTexturesList());
    }
}

void AtlasToolLevel::SetAnimViewerScale(float value, int x, int y)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&AtlasToolLevel::SetAnimViewerScale, this, value, x, y));
    }
    else
#endif
	{
		if (m_AnimViewer)
		{
			m_AnimViewer->SetScaleByPoint(value, x, y);
			//m_AnimViewer->Centering();
		}
	}
}

void AtlasToolLevel::SetPlayStopAnim()
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&AtlasToolLevel::SetPlayStopAnim, this));
    }
    else
#endif
	{
		if (m_AnimViewer)
		{
			if (m_AnimViewer->IsAnimated())
			{
				m_AnimViewer->Stop();
			}
			else
			{
				m_AnimViewer->Play();
			}
		}
	}
}

void AtlasToolLevel::ScrollFramesTo(bool_t toRight)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&AtlasToolLevel::ScrollFramesTo, this, toRight));
    }
    else
#endif
	{
		if (m_AnimViewer)
		{
			if (toRight)
			{
				m_AnimViewer->ScrollFrameRight();
			}
			else
			{
				m_AnimViewer->ScrollFrameLeft();
			}
		}
	}
}

void AtlasToolLevel::SelectAnimation(u32 animation)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&AtlasToolLevel::SelectAnimation, this, animation));
    }
    else
#endif
	{
		if (m_AnimViewer)
		{
			if (m_AnimViewer->GetCurrentAnimation() != animation)
			{
				m_AnimViewer->SetCurrentAnimation(animation);
			}
		}
	}
}

void AtlasToolLevel::SelectFrame(u32 frame)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&AtlasToolLevel::SelectFrame, this, frame));
    }
    else
#endif
	{
		if (m_AnimViewer)
		{
			if (m_AnimViewer->GetCurrentFrame() != frame)
			{
				if (m_AnimViewer->IsAnimated())
				{
					m_AnimViewer->GotoAndPlay(frame);
				}
				else
				{
					m_AnimViewer->GotoAndStop(frame);
				}
			}
		}
	}
}

void AtlasToolLevel::SetAnimationList( SpriteAnimationsListPtr newAnimationList )
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(boost::bind(&AtlasToolLevel::SetAnimationList, this, newAnimationList));
    }
    else
#endif
	{
		if (m_AnimViewer)
		{
			m_AnimViewer->SetAnimationsList(newAnimationList);
		}
	}
}

void AtlasToolLevel::ChangeCursorByState(AnimStates state)
{
	switch(state)
	{
	case ANIM_STATE_IDLE:
		m_OnChangeCursorSignal(0);
		break;
	case ANIM_STATE_MOVE_FRAME:
		m_OnChangeCursorSignal(2);
		break;
	case ANIM_STATE_MOVE_ATLAS:
		m_OnChangeCursorSignal(3);
		break;
	};
}

void AtlasToolLevel::ChangeState(AnimStates state)
{
	if (state != m_PreviousState && state != m_State)
	{
		m_PreviousState = m_State;
	}
	m_State = state;
	ChangeCursorByState(m_State);
}

void AtlasToolLevel::RestoreState()
{
	m_State = m_PreviousState;
	ChangeCursorByState(m_State);
}

//*******************************************************************************
//	SIGNALS
//
//*******************************************************************************
boost::signals::connection AtlasToolLevel::AttachOnFrameBarSelectedSignal( const OnFrameBarSelectedSignal::slot_type& slot )
{
    return m_OnFrameBarSelectedSignal.connect(slot);
}

boost::signals::connection AtlasToolLevel::AttachOnAnimationLoadedSignal(const OnAnimationLoadedSignal::slot_type& slot)
{
	return m_OnAnimationLoadedSignal.connect(slot);
}

boost::signals::connection AtlasToolLevel::AttachOnFrameBarAddFrameSignal(const OnFrameBarAddFrameSignal::slot_type& slot)
{
	return m_OnFrameBarAddFrameSignal.connect(slot);
}

boost::signals::connection AtlasToolLevel::AttachOnPreviewMouseWheelSignal(const OnMouseWheelSignal::slot_type& slot)
{
	return m_OnPreviewMouseWheelSignal.connect(slot);
}

boost::signals::connection AtlasToolLevel::AttachOnFrameBarMouseWheelSignal(const OnMouseWheelSignal::slot_type& slot)
{
	return m_OnFrameBarMouseWheelSignal.connect(slot);
}

boost::signals::connection AtlasToolLevel::AttachOnFrameUpdatedSignal(const OnFrameUpdatedSignal::slot_type &slot)
{
	return m_OnFrameUpdatedSignal.connect(slot);
}

boost::signals::connection AtlasToolLevel::AttachOnChangeCursorSignal(const OnChangeCursorSignal::slot_type &slot)
{
	return m_OnChangeCursorSignal.connect(slot);
}