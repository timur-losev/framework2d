#include "EdAtlasToolWndPresenter.h"
#include "EdViewHolder.h"
#include "EdPresenterHolder.h"
#include "MappingFile.h"
#include "AssetsManager.h"


EdAtlasToolWndPresenter::EdAtlasToolWndPresenter()
	: m_LevelMgr(0)
	, m_SelectedAnimation(0)
	, m_SelectedFrame(0)
{
    m_View = EdViewHolder::getRef().AtlasToolDialog();

    m_FramesList = PTR_NEW(SpriteFramesList());
    m_AnimationsList = PTR_NEW(SpriteAnimationsList());
	m_TexturesList = PTR_NEW(SpriteTexturesNamesList());

    AttachViewSlots();
}

EdAtlasToolWndPresenter::~EdAtlasToolWndPresenter()
{

}

void EdAtlasToolWndPresenter::OnViewShowed()
{
    // The host will manage to delete these objects
    // dont delete it manually
    AtlasToolLevel* level = new AtlasToolLevel();
	
    m_LevelMgr = new CLevelManager();

    m_View->PushLevelManager(m_LevelMgr);
    
    m_LevelMgr->AttachLevel(level);
	AttachModelSlots();
}

void EdAtlasToolWndPresenter::OnButtonNew()
{
	if (!m_SetNameDlgConnection.connected())
		m_SetNameDlgConnection = EdViewHolder::getRef().SetNameForSelectionDialog()->AttachOnOkSignal(boost::bind(&EdAtlasToolWndPresenter::OnShowSetNameDialogOkPressed, this, _1));

    EdPresenterHolder::getRef().ShowSetNameForSelectionDialog();
}

void EdAtlasToolWndPresenter::OnShowSetNameDialogOkPressed( const core::stringc& name )
{
    AnimationDef animation = AnimationDef();
	animation.name = name;

	m_AnimationsList->push_back(animation);
	m_View->RefreshAnimationList(*m_AnimationsList);

	AtlasToolLevel* level = (AtlasToolLevel *)m_LevelMgr->GetLevelByName("AtlasToolLevel");
	if (level)
	{
		level->SetAnimationList(m_AnimationsList);
	}
}	

void EdAtlasToolWndPresenter::OnZoomScrolled(f32 value, int x, int y)
{
	AtlasToolLevel* level = (AtlasToolLevel *)m_LevelMgr->GetLevelByName("AtlasToolLevel");
	if (level)
	{
		level->SetAnimViewerScale(value, x, y);
	}
}

void EdAtlasToolWndPresenter::UpdateView()
{
	
}

void EdAtlasToolWndPresenter::AttachViewSlots()
{

    typedef IEdAtlasToolWndView base;

    m_View->AttachOn(base::ES_ON_SHOW,              boost::bind(&EdAtlasToolWndPresenter::OnViewShowed, this));
    m_View->AttachOn(base::ES_ON_BUTTON_CLICKED,    boost::bind(&EdAtlasToolWndPresenter::OnButtonNew, this));
    m_View->AttachOn(base::ES_ON_PLAY_STOP_ANIM,    boost::bind(&EdAtlasToolWndPresenter::OnPlayStopAnim, this));

    m_View->AttachOn<float, int, int>(base::ES_ON_ZOOM_SCROLLED, boost::bind(&EdAtlasToolWndPresenter::OnZoomScrolled, this, _1, _2, _3));
    
    m_View->AttachOn<io::path>(base::ES_ON_OPEN_FILE,       boost::bind(&EdAtlasToolWndPresenter::OnOpenFile, this, _1));
    m_View->AttachOn<io::path>(base::ES_ON_SAVE_FILE,       boost::bind(&EdAtlasToolWndPresenter::OnSaveFile, this, _1));

    m_View->AttachOn<bool_t>(base::ES_ON_BUTTON_SCROLL,         boost::bind(&EdAtlasToolWndPresenter::OnScrollFrames, this, _1));
    m_View->AttachOn<u32>(base::ES_ON_ANIMATON_SELECTED,        boost::bind(&EdAtlasToolWndPresenter::OnAnimationSelected, this, _1));
    m_View->AttachOn<u32>(base::ES_ON_FRAME_SELECTED,           boost::bind(&EdAtlasToolWndPresenter::OnFrameSelected, this, _1));
    m_View->AttachOn<u32>(base::ES_ON_BUTTON_REMOVE_ANIMATION,  boost::bind(&EdAtlasToolWndPresenter::OnButtonRemoveAnimation, this, _1));
    m_View->AttachOn<u32>(base::ES_ON_BUTTON_REMOVE_FRAME,      boost::bind(&EdAtlasToolWndPresenter::OnButtonRemoveFrame, this, _1));
    m_View->AttachOn<u32, u32>(base::ES_ON_CHANGE_ANIMATION_DURATION,      boost::bind(&EdAtlasToolWndPresenter::OnChangeAnimationDuration, this, _1, _2));

    m_View->AttachOn<u32, int, int>(base::ES_ON_CHANGE_FRAME_OFFSET,      boost::bind(&EdAtlasToolWndPresenter::OnChangeFrameOffset, this, _1, _2, _3));

    m_View->AttachOn
            <
    core::position2df,
    core::vector2di,
    core::position2df,
    core::vector2di
            >
    (base::ES_ON_RESIZE, boost::bind(&EdAtlasToolWndPresenter::OnResize, this, _1, _2, _3, _4));

}

void EdAtlasToolWndPresenter::AttachModelSlots()
{
    AtlasToolLevel* level = (AtlasToolLevel *)m_LevelMgr->GetLevelByName("AtlasToolLevel");
	if (level)
	{
		m_View->AttachOnMouseEvents(level);
		level->AttachOnFrameBarSelectedSignal(boost::bind(&EdAtlasToolWndPresenter::OnFrameBarSelected, this, _1));
		level->AttachOnAnimationLoadedSignal(boost::bind(&EdAtlasToolWndPresenter::OnAnimationLoaded, this, _1, _2, _3));
		level->AttachOnFrameBarAddFrameSignal(boost::bind(&EdAtlasToolWndPresenter::OnAddFrameToAnimation, this, _1));
		level->AttachOnPreviewMouseWheelSignal(boost::bind(&EdAtlasToolWndPresenter::OnPreviewMouseWheel, this, _1, _2, _3, _4));
		level->AttachOnFrameBarMouseWheelSignal(boost::bind(&EdAtlasToolWndPresenter::OnFrameBarMouseWheel, this, _1, _2, _3, _4));
		level->AttachOnFrameUpdatedSignal(boost::bind(&EdAtlasToolWndPresenter::OnFrameChanged, this, _1, _2));
		level->AttachOnChangeCursorSignal(boost::bind(&EdAtlasToolWndPresenter::OnChangeCursor, this, _1));
	}
}

void EdAtlasToolWndPresenter::OnFrameChanged(int index, const FrameDef& frame)
{
	if (m_SelectedAnimation < m_AnimationsList->size() && 
		index >= 0 && index < (int)m_AnimationsList->get(m_SelectedAnimation).frames.size() &&
		index < (int)m_FramesList->size())
	{
		m_FramesList->get(m_AnimationsList->get(m_SelectedAnimation).frames[index]) = frame;
		m_View->SelectFrame(index, m_FramesList->get(m_AnimationsList->get(m_SelectedAnimation).frames[index]));
	}
}

void EdAtlasToolWndPresenter::OnOpenFile(const io::path& fname)
{
	AtlasToolLevel* level = (AtlasToolLevel *)m_LevelMgr->GetLevelByName("AtlasToolLevel");
	if (level)
	{
		level->LoadAnimation(fname);
		level->SetPreviewDimesion(m_View->GetAnimViewerPos(), m_View->GetAnimViewerSize(), m_View->GetFramesBarPos(), m_View->GetFramesBarSize());
	}
}

void EdAtlasToolWndPresenter::OnChangeCursor(int cursor)
{
	m_View->ChangeCursor(cursor);
}

void EdAtlasToolWndPresenter::OnPlayStopAnim()
{
	AtlasToolLevel* level = (AtlasToolLevel *)m_LevelMgr->GetLevelByName("AtlasToolLevel");
	if (level)
	{
		level->SetPlayStopAnim();
	}
}

void EdAtlasToolWndPresenter::OnResize(	const core::position2df& previewPos, 
										const core::vector2di& previewSize, 
										const core::position2df& framesPos, 
										const core::vector2di& framesSize)
{
    if (m_LevelMgr)
    {
        AtlasToolLevel* level = (AtlasToolLevel *)m_LevelMgr->GetLevelByName("AtlasToolLevel");
        if (level)
        {
            level->SetPreviewDimesion(previewPos, previewSize, framesPos, framesSize);
        }
    }
}

void EdAtlasToolWndPresenter::OnScrollFrames(bool_t toRight)
{
	AtlasToolLevel* level = (AtlasToolLevel *)m_LevelMgr->GetLevelByName("AtlasToolLevel");
	if (level)
	{
		level->ScrollFramesTo(toRight);
	}
}

void EdAtlasToolWndPresenter::OnFrameBarSelected(u32 frame)
{
	
}

void EdAtlasToolWndPresenter::OnAddFrameToAnimation(u32 frameNum)
{
	if (m_SelectedAnimation >= 0 && m_SelectedAnimation < m_AnimationsList->size() &&
		frameNum < m_FramesList->size())
	{
		if (++m_SelectedFrame >= m_AnimationsList->get(m_SelectedAnimation).frames.size())
		{
			m_AnimationsList->get(m_SelectedAnimation).frames.push_back(frameNum);
		}
		else if (m_AnimationsList->get(m_SelectedAnimation).frames.size() > 0)
		{
			m_AnimationsList->get(m_SelectedAnimation).frames.insert(frameNum, m_SelectedFrame);
		}
		m_View->RefreshFramesList(m_FramesList, m_AnimationsList->get(m_SelectedAnimation).frames);
		if (m_SelectedFrame < m_AnimationsList->get(m_SelectedAnimation).frames.size())
		{
			m_View->SelectFrame(m_SelectedFrame, m_FramesList->get(m_AnimationsList->get(m_SelectedAnimation).frames[m_SelectedFrame]));
		}

		AtlasToolLevel* level = (AtlasToolLevel *)m_LevelMgr->GetLevelByName("AtlasToolLevel");
		if (level)
		{
			level->SetAnimationList(m_AnimationsList);
		}
	}
}

void EdAtlasToolWndPresenter::OnAnimationLoaded(SpriteAnimationsListPtr animations, SpriteFramesListPtr frames, SpriteTexturesNamesListPtr textures)
{
	m_AnimationsList = animations;
	m_FramesList = frames;
	m_TexturesList = textures;
	m_SelectedAnimation = 0;
	m_SelectedFrame = 0;

	m_View->RefreshAnimationList(*m_AnimationsList);
	m_View->SelectAnimation(m_SelectedAnimation);
	if (m_SelectedAnimation >= 0 && m_SelectedAnimation < m_AnimationsList->size())
	{
		m_View->RefreshFramesList(m_FramesList, m_AnimationsList->get(m_SelectedAnimation).frames);
		if (m_SelectedFrame < m_AnimationsList->get(m_SelectedAnimation).frames.size())
		{
			m_View->SelectFrame(m_SelectedFrame, m_FramesList->get(m_AnimationsList->get(m_SelectedAnimation).frames[m_SelectedFrame]));
		}
	}
}

void EdAtlasToolWndPresenter::OnAnimationSelected(u32 animation)
{
	AtlasToolLevel* level = (AtlasToolLevel *)m_LevelMgr->GetLevelByName("AtlasToolLevel");
	if (level)
	{
		m_SelectedAnimation = animation;
		
		level->SelectAnimation(m_SelectedAnimation);
		if (m_SelectedAnimation >= 0 && m_SelectedAnimation < m_AnimationsList->size())
		{
			m_View->RefreshFramesList(m_FramesList, m_AnimationsList->get(m_SelectedAnimation).frames);
			if (m_SelectedFrame >= m_AnimationsList->get(m_SelectedAnimation).frames.size())
			{
				m_SelectedFrame = m_AnimationsList->get(m_SelectedAnimation).frames.size() - 1;
			}

			if (m_SelectedFrame < m_AnimationsList->get(m_SelectedAnimation).frames.size())
			{
				m_View->SelectFrame(m_SelectedFrame, m_FramesList->get(m_AnimationsList->get(m_SelectedAnimation).frames[m_SelectedFrame]));
			}
		}
	}
}

void EdAtlasToolWndPresenter::OnFrameSelected(u32 frame)
{
	m_SelectedFrame = frame;
	if (m_SelectedAnimation >= 0 && m_SelectedAnimation < m_AnimationsList->size())
	{
  		if (m_SelectedFrame >= m_AnimationsList->get(m_SelectedAnimation).frames.size())
		{
			m_SelectedFrame = m_AnimationsList->get(m_SelectedAnimation).frames.size() - 1;
		}

		if (m_SelectedFrame < m_AnimationsList->get(m_SelectedAnimation).frames.size())
		{
			m_View->SelectFrame(m_SelectedFrame, m_FramesList->get(m_AnimationsList->get(m_SelectedAnimation).frames[m_SelectedFrame]));
		}
	}

	AtlasToolLevel* level = (AtlasToolLevel *)m_LevelMgr->GetLevelByName("AtlasToolLevel");
	if (level)
	{
		level->SelectFrame(m_SelectedFrame);
	}
}

void EdAtlasToolWndPresenter::OnButtonRemoveAnimation(u32 animation)
{
	if (animation >= 0 && animation < m_AnimationsList->size())
	{
		m_AnimationsList->erase(animation);
		if (m_SelectedAnimation >= m_AnimationsList->size())
		{
			m_SelectedAnimation = m_AnimationsList->size() - 1;
		}

		m_View->RefreshAnimationList(*m_AnimationsList);
		if (m_SelectedAnimation < m_AnimationsList->size())
		{
			m_View->RefreshFramesList(m_FramesList, m_AnimationsList->get(m_SelectedAnimation).frames);
		}
		else
		{
			m_View->RefreshFramesList(m_FramesList, core::array<int>());
		}
		m_View->SelectAnimation(m_SelectedAnimation);

		AtlasToolLevel* level = (AtlasToolLevel *)m_LevelMgr->GetLevelByName("AtlasToolLevel");
		if (level)
		{
			level->SetAnimationList(m_AnimationsList);
		}
	}
}

void EdAtlasToolWndPresenter::OnButtonRemoveFrame(u32 frame)
{
	if (m_SelectedAnimation >= 0 && m_SelectedAnimation < m_AnimationsList->size() &&
		frame < m_FramesList->size())
	{
		m_AnimationsList->get(m_SelectedAnimation).frames.erase(frame);
		m_View->RefreshFramesList(m_FramesList, m_AnimationsList->get(m_SelectedAnimation).frames);

		if (m_SelectedFrame >= m_AnimationsList->get(m_SelectedAnimation).frames.size())
		{
			m_SelectedFrame = m_AnimationsList->get(m_SelectedAnimation).frames.size() - 1;
		}

		if (m_SelectedFrame < m_AnimationsList->get(m_SelectedAnimation).frames.size())
		{
			m_View->SelectFrame(m_SelectedFrame, m_FramesList->get(m_AnimationsList->get(m_SelectedAnimation).frames[m_SelectedFrame]));
		}

		AtlasToolLevel* level = (AtlasToolLevel *)m_LevelMgr->GetLevelByName("AtlasToolLevel");
		if (level)
		{
			level->SetAnimationList(m_AnimationsList);
		}
	}
}

void EdAtlasToolWndPresenter::OnChangeAnimationDuration(u32 frame, u32 duration)
{
	if (m_SelectedAnimation >= 0 && m_SelectedAnimation < m_AnimationsList->size() &&
		frame < m_AnimationsList->get(m_SelectedAnimation).frames.size() &&
		frame < m_FramesList->size())
	{
		m_FramesList->get(m_AnimationsList->get(m_SelectedAnimation).frames[frame]).animDuration = duration;
		AtlasToolLevel* level = (AtlasToolLevel *)m_LevelMgr->GetLevelByName("AtlasToolLevel");
		if (level)
		{
			level->SetAnimationList(m_AnimationsList);
		}
	}
}

void EdAtlasToolWndPresenter::OnPreviewMouseWheel(int delta, int direction, int x, int y)
{
	m_View->MouseWheelZoom(direction, x, y);
}

void EdAtlasToolWndPresenter::OnFrameBarMouseWheel(int delta, int direction, int x, int y)
{
	OnScrollFrames(direction > 0);
}

void EdAtlasToolWndPresenter::OnSaveFile(const io::path& fname)
{
	MappingFile::Save(fname, m_FramesList, m_AnimationsList, m_TexturesList, FALSE);
	AssetsManager::getRef().Clear(fname.c_str());	// This asset must be reloaded
}

void EdAtlasToolWndPresenter::OnChangeFrameOffset(u32 frameIndx, int offsetX, int offsetY)
{
	if (m_SelectedAnimation >= 0 && m_SelectedAnimation < m_AnimationsList->size() &&
		frameIndx < m_AnimationsList->get(m_SelectedAnimation).frames.size() &&
		frameIndx < m_FramesList->size())
	{
		m_FramesList->get(m_AnimationsList->get(m_SelectedAnimation).frames[frameIndx]).offsetX = (float)offsetX;
		m_FramesList->get(m_AnimationsList->get(m_SelectedAnimation).frames[frameIndx]).offsetY = (float)offsetY;
		AtlasToolLevel* level = (AtlasToolLevel *)m_LevelMgr->GetLevelByName("AtlasToolLevel");
		if (level)
		{
			level->SetAnimationList(m_AnimationsList);
		}
	}
}
