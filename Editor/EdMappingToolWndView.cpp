#include "EdMappingToolWndView.h"
#include "LevelManager.h"
#include "MappingToolLevel.h"
#include <wx/msgdlg.h>
#include <wx/image.h>
#include <wx/filedlg.h>
#include "CLogger.h"
#include "EdMappingPresenter.h"

static const long ID_SAVE_FILE_TOOL = wxNewId();
static const long ID_OPEN_MAPPING_FILE = wxNewId();
static const long ID_CHANGE_BACK_COLOR = wxNewId();
static const long ID_TRANSPARENT_BACK_COLOR = wxNewId();


EdMappingToolWndView::EdMappingToolWndView( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
	: wxDialog( parent, id, title, pos, size, style )
	, m_ToolBar(NULL)
	, m_scrollBarVertical(NULL)
	, m_ScrollBarHorizontal(NULL)
	, m_stMapList(NULL)
	, m_lbMapList(NULL)
	, m_ButtonAddFrame(NULL)
	, m_ButtonRemoveFrame(NULL)
	, m_ButtonShowHideAll(NULL)
	, m_ButtonRemoveTexture(NULL)
	, m_lbMapListPopup(NULL)
	, m_ViewerSizer(NULL)
	, m_sliderZoom(NULL)
	, m_SelectCursor(wxCURSOR_CROSS )
	, m_MoveCursor(wxCURSOR_SIZING)
{
    SetSizeHints( wxDefaultSize, wxDefaultSize );
	Maximize();
    Centre( wxBOTH );

    InitViewControl();
}

EdMappingToolWndView::~EdMappingToolWndView(void)
{
}

void EdMappingToolWndView::InitViewControl()
{
	wxBoxSizer* m_MainSizer;
	m_MainSizer = new wxBoxSizer( wxVERTICAL );

	wxImage::AddHandler( new wxGIFHandler );
	m_ToolBar = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL ); 
	m_ToolBar->AddTool( ID_OPEN_MAPPING_FILE, wxT("tool"), wxBitmap( wxT("Media/Icons/folder_open.gif"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	m_ToolBar->AddTool( ID_SAVE_FILE_TOOL, wxT("tool"), wxBitmap( wxT("Media/Icons/down.gif"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	m_ToolBar->AddSeparator(); 
	m_ToolBar->AddSeparator(); 
	m_ToolBar->AddSeparator(); 
	m_ToolBar->AddTool( ID_CHANGE_BACK_COLOR, wxT("tool"), wxBitmap( wxT("Media/Icons/close.gif"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	m_ToolBar->AddTool( ID_TRANSPARENT_BACK_COLOR, wxT("tool"), wxBitmap( wxT("Media/Icons/close.gif"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	m_ToolBar->Realize(); 
	
	m_MainSizer->Add( m_ToolBar, 0, wxEXPAND, 5 );

	wxBoxSizer* m_PropsSizer;
	m_PropsSizer = new wxBoxSizer( wxHORIZONTAL );

	wxFlexGridSizer* m_ViewerScrollsSizer;
	m_ViewerScrollsSizer = new wxFlexGridSizer( 2, 2, 0, 0 );
	m_ViewerScrollsSizer->AddGrowableCol( 0 );
	m_ViewerScrollsSizer->AddGrowableRow( 0 );
	m_ViewerScrollsSizer->SetFlexibleDirection( wxBOTH );
	m_ViewerScrollsSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_ViewerSizer = new wxBoxSizer( wxVERTICAL );


	m_ViewerScrollsSizer->Add( m_ViewerSizer, 1, wxEXPAND, 5 );

	wxBoxSizer* m_RightScrollSizer;
	m_RightScrollSizer = new wxBoxSizer( wxHORIZONTAL );

	m_scrollBarVertical = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_VERTICAL );
	m_RightScrollSizer->Add( m_scrollBarVertical, 1, wxALIGN_RIGHT|wxEXPAND, 5 );


	m_ViewerScrollsSizer->Add( m_RightScrollSizer, 0, wxEXPAND, 5 );

	wxBoxSizer* m_BottomScrollSizer;
	m_BottomScrollSizer = new wxBoxSizer( wxVERTICAL );

	m_ScrollBarHorizontal = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	m_BottomScrollSizer->Add( m_ScrollBarHorizontal, 0, wxALIGN_BOTTOM|wxEXPAND, 5 );

	m_sliderZoom = new wxSlider( this, wxID_ANY, 0, -500, 500, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	m_BottomScrollSizer->Add( m_sliderZoom, 1, wxALL|wxEXPAND, 5 );


	m_ViewerScrollsSizer->Add( m_BottomScrollSizer, 0, wxEXPAND, 5 );

	m_PropsSizer->Add( m_ViewerScrollsSizer, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* m_MapSet;
	m_MapSet = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Map Set") ), wxVERTICAL );

	m_stMapList = new wxStaticText( this, wxID_ANY, wxT("Map List"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stMapList->Wrap( -1 );
	m_MapSet->Add( m_stMapList, 0, wxLEFT, 5 );
	
	m_lbMapList = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	m_MapSet->Add( m_lbMapList, 2, wxALL|wxEXPAND, 5 );
	
	m_ButtonAddFrame = new wxButton( this, wxID_ANY, wxT("Add Frames"), wxDefaultPosition, wxDefaultSize, 0 );
	m_MapSet->Add( m_ButtonAddFrame, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	m_ButtonShowHideAll = new wxButton( this, wxID_ANY, wxT("Show/Hide All"), wxDefaultPosition, wxDefaultSize, 0 );
	m_MapSet->Add( m_ButtonShowHideAll, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	m_ButtonRemoveFrame = new wxButton( this, wxID_ANY, wxT("Remove Frame"), wxDefaultPosition, wxDefaultSize, 0 );
	m_MapSet->Add( m_ButtonRemoveFrame, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );

	m_stTextureList = new wxStaticText( this, wxID_ANY, wxT("Textures List"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stTextureList->Wrap( -1 );
	m_MapSet->Add( m_stTextureList, 0, wxLEFT, 5 );

	m_lbTextureList = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	m_MapSet->Add( m_lbTextureList, 1, wxALL|wxEXPAND, 5 );
	
	m_ButtonAddTexture = new wxButton( this, wxID_ANY, wxT("Add Texture"), wxDefaultPosition, wxDefaultSize, 0 );
	m_MapSet->Add( m_ButtonAddTexture, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	m_ButtonRemoveTexture = new wxButton( this, wxID_ANY, wxT("Remove Texture"), wxDefaultPosition, wxDefaultSize, 0 );
	m_MapSet->Add( m_ButtonRemoveTexture, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );

	m_PropsSizer->Add( m_MapSet, 0, wxEXPAND, 5 );


	m_MainSizer->Add( m_PropsSizer, 1, wxEXPAND, 5 );


	this->SetSizer( m_MainSizer );
	this->Layout();
    this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(EdMappingToolWndView::OnClose));
    this->Connect(ID_OPEN_MAPPING_FILE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(EdMappingToolWndView::OnOpenMappingFile));
    this->Connect(ID_SAVE_FILE_TOOL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(EdMappingToolWndView::OnSaveToFile));
	this->Connect(wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(EdMappingToolWndView::OnZoomScrolled));
	this->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EdMappingToolWndView::OnButtonClicked));
	this->Connect(wxEVT_SIZE, wxSizeEventHandler(EdMappingToolWndView::OnResizeWindow));
	this->Connect(wxEVT_UPDATE_UI, wxCommandEventHandler(EdMappingToolWndView::OnUpdate));
	this->Connect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(EdMappingToolWndView::OnListBoxSelected));
	this->Connect(m_ButtonAddTexture->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EdMappingToolWndView::OnOpenImage));
	this->Connect(m_ButtonRemoveTexture->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EdMappingToolWndView::RemoveTexture));
	this->Connect(m_ButtonRemoveFrame->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EdMappingToolWndView::RemoveFrame));
	//this->Connect(m_lbMapList->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(EdMappingToolWndView::OnSelectFrameList));
	this->Connect(ID_CHANGE_BACK_COLOR, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(EdMappingToolWndView::OnChangeBackgroundColor));
	this->Connect(ID_TRANSPARENT_BACK_COLOR, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(EdMappingToolWndView::OnChangeBackgroundColor));
}

void EdMappingToolWndView::MouseWheelZoom(int direction, int x, int y)
{
	m_sliderZoom->SetValue(m_sliderZoom->GetValue() + direction / 7);

	float scale = 1;
	scale += (float)m_sliderZoom->GetValue() * ((m_sliderZoom->GetValue() > 0) ? 10 : 1) / m_sliderZoom->GetMax();
	if (scale < 0) scale = 0;

    CallBack(IEdMappingToolWndView::ES_ON_ZOOM_SCROLLED, scale, x, y);
}

void EdMappingToolWndView::RefreshFramesList(const SpriteFramesListPtr& frames)
{
	m_lbMapList->Clear();

	for (u32 i = 0; i < frames->size(); ++i)
	{
	    std::ostringstream ss;
        const FrameDef& frame = frames->get(i);
		ss << frame.name.c_str() << " " << frame.x << "," << frame.y << ":" << frame.width << "," << frame.height;

		m_lbMapList->Append(_(ss.str().c_str()));
	}
}

void EdMappingToolWndView::RefreshTexturesList(const SpriteTexturesNamesListPtr& names)
{
	m_lbTextureList->Clear();

	for (u32 i = 0; i < names->size(); ++i)
	{
	    std::ostringstream ss;
		ss << names->get(i).c_str();

		m_lbTextureList->Append(_(ss.str().c_str()));
	}
}

void EdMappingToolWndView::ClearSelections()
{
    CallBack(IEdMappingToolWndView::ES_ON_CLEAR_SELECTION);
}

const core::position2df EdMappingToolWndView::GetMapViewerPos()
{
	if (m_ViewerSizer)
	{
		return core::position2df(m_ViewerSizer->GetPosition().x, m_ViewerSizer->GetPosition().y);
	}

	return core::position2df(0, 0);
}

const core::vector2di EdMappingToolWndView::GetMapViewerSize()
{
	if (m_ViewerSizer)
	{
		return core::vector2di(m_ViewerSizer->GetSize().GetWidth(), m_ViewerSizer->GetSize().GetHeight());
	}

	return core::vector2di(0, 0);
}

int EdMappingToolWndView::GetSelectedFrameIndex()
{
	return m_lbMapList->GetSelection();
}

void EdMappingToolWndView::ChangeCursor(int cursor)
{
	switch(cursor)
	{
	case CURSOR_DEFAULT:
		this->SetCursor(wxCURSOR_DEFAULT);
		break;
	case CURSOR_SELECT:
		this->SetCursor(m_SelectCursor);
		break;
	case CURSOR_MOVE:
		this->SetCursor(m_MoveCursor);
		break;
	case CURSOR_HAND:
		this->SetCursor(wxCURSOR_HAND);
		break;
	default:
		this->SetCursor(wxCURSOR_DEFAULT);
		break;
	};
}

//*******************************************************************************
//	WXWIDGETS HANDLERS
//
//*******************************************************************************
void EdMappingToolWndView::OnClearSelections( wxCommandEvent& evt )
{
    ClearSelections();
}

void EdMappingToolWndView::OnSaveToFile( wxCommandEvent& evt )
{
    wxFileDialog dlg(this, _("Save mapping file"), wxEmptyString, wxEmptyString, _("Mapping file (*.mpf)|*.mpf|All Files (*.*)|*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT,
        wxDefaultPosition);

    if (dlg.ShowModal() == wxID_OK)
    {
        wxString filenp = dlg.GetPath();

        io::path txtpath = (const fschar_t*)filenp.c_str();
        CallBack(IEdMappingToolWndView::ES_ON_SAVE_MAPPING_FILE, txtpath);
    }

    dlg.Destroy();

    evt.Skip();
}

void EdMappingToolWndView::OnListBoxSelected(wxCommandEvent & evt)
{
	if (m_lbMapList->GetId() == evt.GetId())
	{
		int index = m_lbMapList->GetSelection();
        CallBack(IEdMappingToolWndView::ES_ON_CHANGE_SELECTED_FRAME, index);
	}
	else if (m_lbTextureList->GetId() == evt.GetId())
	{
		int index = m_lbTextureList->GetSelection();
        CallBack(IEdMappingToolWndView::ES_ON_CHANGE_CURRENT_TEXTURE, index);
	}

	evt.Skip();
}

void EdMappingToolWndView::ListBoxOnContextMenu( wxMouseEvent &evt )
{
    //if (m_lbMapList->GetSelection() == wxNOT_FOUND) return;
    int item = m_lbMapList->HitTest(evt.GetPosition());

    if (wxNOT_FOUND == item) return;

    m_lbMapList->Select(item);

    m_lbMapList->PopupMenu(m_lbMapListPopup, evt.GetPosition());
}

void EdMappingToolWndView::OnButtonClicked( wxCommandEvent & evt )
{
	if (m_ButtonAddFrame->GetId() == evt.GetId())
	{
		CallBack(IEdMappingToolWndView::ES_ON_BUTTON_ADD_FRAME);
		ChangeCursor(CURSOR_SELECT);
	}
	else if (m_ButtonShowHideAll->GetId() == evt.GetId())
	{
        CallBack(IEdMappingToolWndView::ES_ON_BUTTON_SHOW_HIDE_FRAMES);
		ChangeCursor(CURSOR_DEFAULT);
	}

    evt.Skip();
}

void EdMappingToolWndView::OnClose( wxCloseEvent & evt )
{
    APP_API_ASSERT(m_Render);

    m_Render->Close();
    m_Render.reset();
    
    evt.Skip();
}

void EdMappingToolWndView::InstantiateRender()
{
    m_Render.reset(new WxIrrControl(this, wxID_ANY, wxPoint(0, m_ToolBar->GetSize().GetHeight()), m_ViewerSizer->GetSize(), 0, wxDefaultValidator, _T("MappingToolControl")));
    m_Render->AttachOnWorkerInitDoneSignal(boost::bind(&EdMappingToolWndView::SendOnShow, this));

    if (!m_Render->Init())
        wxMessageBox(wxT("Failed to initialize."), wxT("Error"), wxICON_ERROR);
    else
    {
        m_Render->Show();
        m_Render->Start();
    }
}

bool EdMappingToolWndView::Show( bool show )
{
    bool ret = wxDialog::Show(show);

    if (show)
        InstantiateRender();

    return ret;
}

void EdMappingToolWndView::SendOnShow()
{
    CallBack(IEdMappingToolWndView::ES_ON_SHOW);
}

void EdMappingToolWndView::OnOpenImage(wxCommandEvent& evt)
{
    wxFileDialog dlg(this, _("Choose an image to open"), wxEmptyString, wxEmptyString, _("PNG images (*.png)|*.png|PVR images (*.pvr)|*.pvr|All Files (*.*)|*.*"), wxFD_OPEN, wxDefaultPosition);

    if (dlg.ShowModal() == wxID_OK)
    {
		core::stringc fname = (const char*)dlg.GetFilename().c_str();
		//fname = fname.subString(0, fname.find("."));

        CallBack(IEdMappingToolWndView::ES_ON_OPEN_IMAGE, fname);
    }

    dlg.Destroy();

    evt.Skip();
}

void EdMappingToolWndView::OnChangeBackgroundColor(wxCommandEvent& evt)
{
	if (ID_CHANGE_BACK_COLOR == evt.GetId())
	{
		wxColourDialog * dialog = new wxColourDialog(this);

		dialog->Centre();
		if(dialog->ShowModal() == wxID_OK)
		{
			wxColour colour = dialog->GetColourData().GetColour();
			m_Render->SetColorFill(video::SColor(255, colour.Red(), colour.Green(), colour.Blue()));
		}

		dialog->Destroy();
	}
	else if (ID_TRANSPARENT_BACK_COLOR == evt.GetId())
	{
		m_Render->SetColorFill(video::SColor(0, 0, 0, 0));
	}

	evt.Skip();
}

void EdMappingToolWndView::OnOpenMappingFile( wxCommandEvent& evt )
{
    wxFileDialog dlg(this, _("Choose a mapping file to open"), wxEmptyString, wxEmptyString, _("Mapping file (*.mpf)|*.mpf|All Files (*.*)|*.*"), wxFD_OPEN, wxDefaultPosition);

    if (dlg.ShowModal() == wxID_OK)
    {
		core::stringc fname = (const char*)dlg.GetPath().c_str();
		//fname = fname.subString(0, fname.find("."));

        CallBack(IEdMappingToolWndView::ES_ON_OPEN_MAPPING_FILE, fname);
    }

    dlg.Destroy();

    evt.Skip();
}

void EdMappingToolWndView::OnZoomScrolled( wxScrollEvent & evt )
{
	if (m_sliderZoom->GetId() == evt.GetId())
	{
		float scale = 1;
		scale += (float)m_sliderZoom->GetValue() * ((m_sliderZoom->GetValue() > 0) ? 10 : 1) / m_sliderZoom->GetMax();
		if (scale < 0) scale = 0;

        CallBack(IEdMappingToolWndView::ES_ON_ZOOM_SCROLLED, scale, 
            m_ViewerSizer->GetPosition().x + m_ViewerSizer->GetSize().x / 2, 
            m_ViewerSizer->GetPosition().y + m_ViewerSizer->GetSize().y / 2);
	}

    evt.Skip();
}

void EdMappingToolWndView::OnResizeWindow(wxSizeEvent &evt)
{
	m_IsResized = TRUE;
	
	evt.Skip();
}

void EdMappingToolWndView::OnUpdate(wxCommandEvent &evt)
{
	if (m_IsResized && m_ViewerSizer && m_Render)
	{
		m_IsResized = FALSE;

		m_Render->Resize(m_ViewerSizer->GetSize().GetWidth(), m_ViewerSizer->GetSize().GetHeight());
		CallBack(IEdMappingToolWndView::ES_ON_RESIZE, core::position2df(m_ViewerSizer->GetPosition().x, m_ViewerSizer->GetPosition().y), 
						                              core::vector2di(m_ViewerSizer->GetSize().GetWidth(), m_ViewerSizer->GetSize().GetHeight()));

		this->Refresh();
	}
	evt.Skip();
}

void EdMappingToolWndView::SetNameOnMenuSelection( wxCommandEvent& evt )
{
    CallBack(IEdMappingToolWndView::ES_ON_SET_NAME_FOR_SELECTION);
}

void EdMappingToolWndView::RemoveFrame(wxCommandEvent & evt)
{
	int index = m_lbMapList->GetSelection();
    CallBack(IEdMappingToolWndView::ES_ON_REMOVE_FRAME, index);
}

void EdMappingToolWndView::RemoveTexture(wxCommandEvent & evt)
{
	int index = m_lbTextureList->GetSelection();
    CallBack(IEdMappingToolWndView::ES_ON_REMOVE_TEXTURE, index);
}

void EdMappingToolWndView::OnSelectFrameList(wxCommandEvent & evt)
{
	int index = m_lbMapList->GetSelection();
    CallBack(IEdMappingToolWndView::ES_ON_CHANGE_SELECTED_FRAME);
}

//*******************************************************************************
//	SIGNALS
//
//*******************************************************************************

void EdMappingToolWndView::PushLevelManager( CLevelManager* lmgr )
{
    if (m_Render)
        m_Render->PushLevelManager(lmgr);
}

void EdMappingToolWndView::AttachOnMouseEvents( MappingToolLevel* lvl )
{
    m_Render->AttachOnMouseDownSignal(boost::bind(&MappingToolLevel::OnMouseDown, lvl, _1, _2, _3));
    m_Render->AttachOnMouseUpSignal(boost::bind(&MappingToolLevel::OnMouseUp, lvl, _1, _2, _3));
    m_Render->AttachOnMouseMovedSignal(boost::bind(&MappingToolLevel::OnMouseMove, lvl, _1, _2));
	m_Render->AttachMouseWheelSignal(boost::bind(&MappingToolLevel::OnMouseWheel, lvl, _1, _2, _3, _4));
}
