#include "EdMappingPresenter.h"
#include "EdViewHolder.h"
#include "EdPresenterHolder.h"
#include "MappingFile.h"
#include "CLogger.h"
#include "AssetsManager.h"

EdMappingPresenter::EdMappingPresenter()
	: m_Level(NULL)
{
    m_View = EdViewHolder::getRef().MappingToolDialog();

    m_FramesList = PTR_NEW(SpriteFramesList());
    m_TexturesList = PTR_NEW(SpriteTexturesNamesList());
	m_AnimationsList = PTR_NEW(SpriteAnimationsList());

    AttachViewSlots();
}

EdMappingPresenter::~EdMappingPresenter()
{

}



//*******************************************************************************
//	
//
//*******************************************************************************
void EdMappingPresenter::OnViewShowed()
{
	m_TexturesList->clear();
	m_FramesList->clear();

	m_View->RefreshFramesList(m_FramesList);
	m_View->RefreshTexturesList(m_TexturesList);

    m_Level = new MappingToolLevel();
    m_LevelMgr = new CLevelManager();

    m_View->PushLevelManager(m_LevelMgr);

    m_LevelMgr->AttachLevel(m_Level);    

	m_Level->SetPreviewDimesion(m_View->GetMapViewerPos(), m_View->GetMapViewerSize());
    AttachModelSlots();
}

void EdMappingPresenter::OnOpenImage(const io::path& path)
{
    APP_API_ASSERT(m_Level);

	for (u32 i = 0; i < m_TexturesList->size(); ++i)
	{
		if (core::stringc(path) == m_TexturesList->get(i))
		{
			return;
		}
	}

	m_TexturesList->push_back(path); 
	m_Level->LoadImage(path);
	m_View->RefreshFramesList(m_FramesList);
	m_View->RefreshTexturesList(m_TexturesList);
}

void EdMappingPresenter::OnClearSelections()
{
    m_Level->ClearFrames();
}

void EdMappingPresenter::OnSelectionAdded(const FrameDef& frame)
{
	m_FramesList->push_back(frame);
	m_View->RefreshFramesList(m_FramesList);
}

void EdMappingPresenter::OnFrameChanged(int index, const FrameDef& frame)
{
	if (index >= 0 && index < (int)m_FramesList->size())
	{
		m_FramesList->get(index) = frame;
		m_View->RefreshFramesList(m_FramesList);
	}
}

void EdMappingPresenter::OnSaveMappingFile(const io::path& path)
{
    if (MappingFile::Save(path, m_FramesList, m_AnimationsList, m_TexturesList, FALSE))
	{
		AssetsManager::getRef().Clear(path.c_str());	// This asset must be reloaded
	}
	else
	{
		LogMessage(LOG_ERR, "Unable to save mapping file " << path.c_str());
	}		
}

void EdMappingPresenter::OnShowSetNameDialog()
{
    EdViewHolder::getRef().SetNameForSelectionDialog()->AttachOnOkSignal(boost::bind(&EdMappingPresenter::OnShowSetNameDialogOkPressed, this, _1));

    EdPresenterHolder::getRef().ShowSetNameForSelectionDialog();
}

void EdMappingPresenter::OnShowSetNameDialogOkPressed( const core::stringc& name )
{
    int item = m_View->GetSelectedFrameIndex();
    m_Level->ChangeName(item, name);
}

void EdMappingPresenter::OnOpenMappingFile( const io::path& path)
{
	m_FramesList->clear();
	m_TexturesList->clear();

    if (!AssetsManager::getRef().GetMapping(path, m_FramesList, m_AnimationsList, m_TexturesList))
        APP_API_ASSERT(FALSE);
	
	m_Level->LoadMapFile(path);
	m_View->RefreshFramesList(m_FramesList);
	m_View->RefreshTexturesList(m_TexturesList);
}

void EdMappingPresenter::OnZoomScrolled(f32 value, int x, int y)
{
	if (m_Level)
	{
		m_Level->SetMapViewerScale(value, x, y);
	}
}

void EdMappingPresenter::OnPreviewMouseWheel(int delta, int direction, int x, int y)
{
	m_View->MouseWheelZoom(direction, x, y);
}

void EdMappingPresenter::OnFrameSelecting()
{
	if (m_Level)
	{
		m_Level->SetOperation(MAP_STATE_SELECTING_FRAME);
	}
}

void EdMappingPresenter::OnShowHideSelections()
{
	if (m_Level)
	{
		m_Level->ShowHideAllSelections();
	}
}

void EdMappingPresenter::OnChangeCursor(int cursor)
{
	m_View->ChangeCursor(cursor);
}

void EdMappingPresenter::OnResize(const core::position2df& previewPos, const core::vector2di& previewSize)
{
	if (m_Level)
	{
		m_Level->SetPreviewDimesion(previewPos, previewSize);
	}
}

void EdMappingPresenter::OnChangeCurrentTexture(int index)
{
	if (m_Level)
	{
		m_Level->ChangeCurrentTexture(index);
	}
}

void EdMappingPresenter::OnRemoveFrame(int index)
{
	if (index >= 0 && index < (int)m_FramesList->size())
	{
		m_FramesList->erase(index);
		m_Level->RemoveFrame(index);
		m_View->RefreshFramesList(m_FramesList);
	}
}

void EdMappingPresenter::OnRemoveTexture(int index)
{
	if (index < (int)m_TexturesList->size())
	{
		m_TexturesList->erase(index);
		m_Level->RemoveTexture(index);
		m_View->RefreshFramesList(m_FramesList);
		m_View->RefreshTexturesList(m_TexturesList);
	}
}

void EdMappingPresenter::OnChangeSelectedFrame(int index)
{
	if (m_Level)
	{
		m_Level->ChangeSelectedFrame(index);
	}
}

//*******************************************************************************
//	
//
//*******************************************************************************
void EdMappingPresenter::UpdateView()
{

}

void EdMappingPresenter::AttachViewSlots()
{
    
    m_View->AttachOn<io::path>(IEdMappingToolWndView::ES_ON_OPEN_IMAGE,        boost::bind(&EdMappingPresenter::OnOpenImage, this, _1));
    m_View->AttachOn<io::path>(IEdMappingToolWndView::ES_ON_SAVE_MAPPING_FILE, boost::bind(&EdMappingPresenter::OnSaveMappingFile, this, _1));
    m_View->AttachOn<io::path>(IEdMappingToolWndView::ES_ON_OPEN_MAPPING_FILE, boost::bind(&EdMappingPresenter::OnOpenMappingFile, this, _1));

    m_View->AttachOn<f32, int, int>(IEdMappingToolWndView::ES_ON_ZOOM_SCROLLED,               boost::bind(&EdMappingPresenter::OnZoomScrolled, this, _1, _2, _3));
    m_View->AttachOn<core::position2df, core::vector2di>(IEdMappingToolWndView::ES_ON_RESIZE, boost::bind(&EdMappingPresenter::OnResize, this, _1, _2));

    m_View->AttachOn(IEdMappingToolWndView::ES_ON_BUTTON_ADD_FRAME,         boost::bind(&EdMappingPresenter::OnFrameSelecting, this));
    m_View->AttachOn(IEdMappingToolWndView::ES_ON_BUTTON_SHOW_HIDE_FRAMES,  boost::bind(&EdMappingPresenter::OnShowHideSelections, this));
    m_View->AttachOn(IEdMappingToolWndView::ES_ON_SHOW,                     boost::bind(&EdMappingPresenter::OnViewShowed, this));
    m_View->AttachOn(IEdMappingToolWndView::ES_ON_CLEAR_SELECTION,          boost::bind(&EdMappingPresenter::OnClearSelections, this));
    m_View->AttachOn(IEdMappingToolWndView::ES_ON_SET_NAME_FOR_SELECTION,   boost::bind(&EdMappingPresenter::OnShowSetNameDialog, this));

	m_View->AttachOn<int>(IEdMappingToolWndView::ES_ON_CHANGE_CURRENT_TEXTURE, boost::bind(&EdMappingPresenter::OnChangeCurrentTexture, this, _1));
	m_View->AttachOn<int>(IEdMappingToolWndView::ES_ON_REMOVE_FRAME,           boost::bind(&EdMappingPresenter::OnRemoveFrame, this, _1));
	m_View->AttachOn<int>(IEdMappingToolWndView::ES_ON_REMOVE_TEXTURE,         boost::bind(&EdMappingPresenter::OnRemoveTexture, this, _1));
	m_View->AttachOn<int>(IEdMappingToolWndView::ES_ON_CHANGE_SELECTED_FRAME,  boost::bind(&EdMappingPresenter::OnChangeSelectedFrame, this, _1));
}

void EdMappingPresenter::AttachModelSlots()
{
    m_View->AttachOnMouseEvents(m_Level);
    m_Level->AttachOnSelectionAddedSignal(boost::bind(&EdMappingPresenter::OnSelectionAdded, this, _1));
	m_Level->AttachOnFrameBarMouseWheelSignal(boost::bind(&EdMappingPresenter::OnPreviewMouseWheel, this, _1, _2, _3, _4));
	m_Level->AttachOnChangeCursorSignal(boost::bind(&EdMappingPresenter::OnChangeCursor, this, _1));
	m_Level->AttachOnFrameUpdatedSignal(boost::bind(&EdMappingPresenter::OnFrameChanged, this, _1, _2));
}
