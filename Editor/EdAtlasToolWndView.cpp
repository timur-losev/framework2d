#include "EdAtlasToolWndView.h"
#include "LevelManager.h"
#include "AtlasToolLevel.h"

static const long wxID_OPEN_FILE = wxNewId();
static const long wxID_SAVE_FILE = wxNewId();
static const long ID_CHANGE_BACK_COLOR = wxNewId();
static const long ID_TRANSPARENT_BACK_COLOR = wxNewId();

EdAtlasToolWndView::EdAtlasToolWndView( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) 
	: wxDialog( parent, id, title, pos, size, style )
	, m_sliderZoom(0)
	, m_stAnimList(0)
	, m_lbAnimList(0)
	, m_ButtonNew(0)
	, m_ButtonRemoveAnim(0)
	, m_stFrames(0)
	, m_lbFrames(0)
	, m_Duration(0)
	, m_ButtonPlayAnim(0)
	, m_ButtonRemoveFrame(0)
	, m_ButtonLeft(0)
	, m_ButtonRight(0)
	, m_AnimViewerSizer(0)
	, m_FramesSizer(0)
	, m_IsResized(FALSE)
	, m_SelectCursor(wxCURSOR_CROSS )
	, m_MoveCursor(wxCURSOR_SIZING)
    , m_IsShown(FALSE)
    {
    SetSizeHints( wxDefaultSize, wxDefaultSize );
	//SetSize(800, 600);
    Centre( wxBOTH );
    
    //InitAnimEditor();
}

EdAtlasToolWndView::~EdAtlasToolWndView()
{
}

void EdAtlasToolWndView::InitViewControl()
{
    this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(EdAtlasToolWndView::OnClose));
	this->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EdAtlasToolWndView::OnButtonClicked));
	this->Connect(wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(EdAtlasToolWndView::OnZoomScrolled));  
	this->Connect(wxID_OPEN_FILE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(EdAtlasToolWndView::OnOpenFileClicked));
	this->Connect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(EdAtlasToolWndView::OnAnimationSelected));
	this->Connect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxCommandEventHandler(EdAtlasToolWndView::OnAnimationDurationChanged));
	this->Connect(wxID_SAVE_FILE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(EdAtlasToolWndView::OnSaveFileClicked));
	this->Connect(wxEVT_SIZE, wxSizeEventHandler(EdAtlasToolWndView::OnResizeWindow));
	this->Connect(wxEVT_UPDATE_UI, wxCommandEventHandler(EdAtlasToolWndView::OnUpdate));
	this->Connect(ID_CHANGE_BACK_COLOR, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(EdAtlasToolWndView::OnChangeBackgroundColor));
	this->Connect(ID_TRANSPARENT_BACK_COLOR, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(EdAtlasToolWndView::OnChangeBackgroundColor));
}

void EdAtlasToolWndView::DeInitViewControl()
{
    this->Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(EdAtlasToolWndView::OnClose));
	this->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EdAtlasToolWndView::OnButtonClicked));
	this->Disconnect(wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(EdAtlasToolWndView::OnZoomScrolled));  
	this->Disconnect(wxID_OPEN_FILE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(EdAtlasToolWndView::OnOpenFileClicked));
	this->Disconnect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(EdAtlasToolWndView::OnAnimationSelected));
	this->Disconnect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxCommandEventHandler(EdAtlasToolWndView::OnAnimationDurationChanged));
	this->Disconnect(wxID_SAVE_FILE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(EdAtlasToolWndView::OnSaveFileClicked));
	this->Disconnect(wxEVT_SIZE, wxSizeEventHandler(EdAtlasToolWndView::OnResizeWindow));
	this->Disconnect(wxEVT_UPDATE_UI, wxCommandEventHandler(EdAtlasToolWndView::OnUpdate));
	this->Disconnect(ID_CHANGE_BACK_COLOR, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(EdAtlasToolWndView::OnChangeBackgroundColor));
	this->Disconnect(ID_TRANSPARENT_BACK_COLOR, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(EdAtlasToolWndView::OnChangeBackgroundColor));
}

bool EdAtlasToolWndView::Show( bool show )
{
    bool ret = wxDialog::Show(show);

    if (show)
    {
        m_IsShown = TRUE;
        Maximize();
        InitViewControl();
    }

    return ret;
}

void EdAtlasToolWndView::SendOnShow()
{
    CallBack(ES_ON_SHOW);
    m_IsResized = TRUE;
}

void EdAtlasToolWndView::OnClose( wxCloseEvent & evt )
{
	DeInitViewControl();
    m_Render->Close();
    m_Render.reset();

    evt.Skip();
}

void EdAtlasToolWndView::OnButtonClicked( wxCommandEvent & evt )
{
	if (m_ButtonPlayAnim->GetId() == evt.GetId())
	{
        CallBack(ES_ON_PLAY_STOP_ANIM);
	}
	else if (m_ButtonLeft->GetId() == evt.GetId())
	{
        CallBack<bool_t>(ES_ON_BUTTON_SCROLL, FALSE);
	}
	else if (m_ButtonRight->GetId() == evt.GetId())
	{
		CallBack<bool_t>(ES_ON_BUTTON_SCROLL, FALSE);
	}
	else if (m_ButtonNew->GetId() == evt.GetId())
	{
        CallBack(ES_ON_BUTTON_CLICKED);
	}
	else if (m_ButtonRemoveAnim->GetId() == evt.GetId())
	{
		u32 animation = m_lbAnimList->GetSelection();
        CallBack(ES_ON_BUTTON_REMOVE_ANIMATION, animation);
	}
	else if (m_ButtonRemoveFrame->GetId() == evt.GetId())
	{
		u32 frame = m_lbFrames->GetSelection();
        CallBack(ES_ON_BUTTON_REMOVE_FRAME, frame);
	}

    evt.Skip();
}

void EdAtlasToolWndView::OnOpenFileClicked(wxCommandEvent & evt)
{
	wxFileDialog dlg(this, _("Choose an image to open"), wxEmptyString, wxEmptyString, _("MAP files (*.mpf)|*.mpf|All Files (*.*)|*.*"), wxFD_OPEN, wxDefaultPosition);

    if (dlg.ShowModal() == wxID_OK)
    {
		io::path fname = (const char*)dlg.GetPath().c_str();
		//fname = fname.subString(0, fname.find("."));

        CallBack(ES_ON_OPEN_FILE, fname);
    }

    dlg.Destroy();

    evt.Skip();
}

void EdAtlasToolWndView::OnSaveFileClicked(wxCommandEvent & evt)
{
	wxFileDialog dlg(this, _("Choose an image to open"), wxEmptyString, wxEmptyString, _("Mapping file (*.mpf)|*.mpf|All Files (*.*)|*.*"), wxFD_SAVE, wxDefaultPosition);

    if (dlg.ShowModal() == wxID_OK)
    {
		io::path fname = (const char*)dlg.GetPath().c_str();

        CallBack(ES_ON_SAVE_FILE, fname);
    }

    dlg.Destroy();

    evt.Skip();
}

void EdAtlasToolWndView::OnZoomScrolled( wxScrollEvent & evt )
{
	if (m_sliderZoom->GetId() == evt.GetId())
	{
		float scale = 1;
		scale += (float)m_sliderZoom->GetValue() * ((m_sliderZoom->GetValue() > 0) ? 10 : 1) / m_sliderZoom->GetMax();
		if (scale < 0) scale = 0;

        CallBack<float, int, int>(ES_ON_ZOOM_SCROLLED, scale,
                m_AnimViewerSizer->GetPosition().x + m_AnimViewerSizer->GetSize().x / 2, m_AnimViewerSizer->GetPosition().y + m_AnimViewerSizer->GetSize().y / 2);
	}
}

void EdAtlasToolWndView::OnAnimationSelected(wxCommandEvent & evt)
{
	if (m_lbAnimList->GetId() == evt.GetId())
	{
		u32 animation = m_lbAnimList->GetSelection();
        CallBack(ES_ON_ANIMATON_SELECTED, animation);
	}
	else if (m_lbFrames->GetId() == evt.GetId())
	{
		u32 frame = m_lbFrames->GetSelection();
        CallBack(ES_ON_FRAME_SELECTED, frame);
	}

	evt.Skip();
}

void EdAtlasToolWndView::OnAnimationDurationChanged(wxCommandEvent & evt)
{
	if (m_Duration->GetId() == evt.GetId())
	{
		u32 frameIndx = m_lbFrames->GetSelection();
		u32 duration = m_Duration->GetValue();
        CallBack(ES_ON_CHANGE_ANIMATION_DURATION, frameIndx, duration);
	}
	else if (m_OffsetX->GetId() == evt.GetId() ||
			 m_OffsetY->GetId() == evt.GetId())
	{
		u32 frameIndx = m_lbFrames->GetSelection();
		int offsetX = m_OffsetX->GetValue();
		int offsetY = m_OffsetY->GetValue();
        CallBack(ES_ON_CHANGE_FRAME_OFFSET, frameIndx, offsetX, offsetY);
	}

	evt.Skip();
}

void EdAtlasToolWndView::OnResizeWindow(wxSizeEvent &evt)
{
	m_IsResized = TRUE;
	
	evt.Skip();
}

void EdAtlasToolWndView::OnUpdate(wxCommandEvent &evt)
{
	if (m_IsResized && m_MainSizer && m_Render && 0)
	{
		m_IsResized = FALSE;

        int w = m_MainSizer->GetSize().GetWidth();
        int h = m_MainSizer->GetSize().GetHeight();

		m_Render->Resize(w,h);
		CallBack(ES_ON_RESIZE, 
                 GetAnimViewerPos(),
                 GetAnimViewerSize(),
				 GetFramesBarPos(),
                 GetFramesBarSize());

		Refresh();
	}
    else if (m_IsShown == TRUE && !m_Render)
    {
        m_IsShown = FALSE;
        InstantiateRender();
    }
    else
        evt.Skip();
}

void EdAtlasToolWndView::OnChangeBackgroundColor(wxCommandEvent& evt)
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

void EdAtlasToolWndView::MouseWheelZoom(int direction, int x, int y)
{
	m_sliderZoom->SetValue(m_sliderZoom->GetValue() + direction / 7);

	float scale = 1;
	scale += (float)m_sliderZoom->GetValue() * ((m_sliderZoom->GetValue() > 0) ? 10 : 1) / m_sliderZoom->GetMax();
	if (scale < 0) scale = 0;

    CallBack(ES_ON_ZOOM_SCROLLED, scale, x ,y);
}

void EdAtlasToolWndView::InitAnimEditor()
{
	m_MainSizer = new wxBoxSizer( wxVERTICAL );

	m_MainSizer->SetMinSize( wxSize( -1,80 ) ); 

    wxImage::AddHandler( new wxGIFHandler );
	m_ToolBar = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL );
	m_ToolBar->AddTool( wxID_OPEN_FILE, wxT("Open"), wxBitmap( wxT("Media/Icons/folder_open.gif"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );
	m_ToolBar->AddTool( wxID_SAVE_FILE, wxT("Save"), wxBitmap( wxT("Media/Icons/down.gif"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );
	m_ToolBar->AddSeparator();
	m_ToolBar->AddSeparator();
	m_ToolBar->AddTool( ID_CHANGE_BACK_COLOR, wxT("tool"), wxBitmap( wxT("Media/Icons/close.gif"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );
	m_ToolBar->AddTool( ID_TRANSPARENT_BACK_COLOR, wxT("tool"), wxBitmap( wxT("Media/Icons/close.gif"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_ToolBar->Realize();

	m_MainSizer->Add( m_ToolBar, 0, wxEXPAND, 5 );

	wxBoxSizer* propsSizer = new wxBoxSizer( wxHORIZONTAL );
	propsSizer->SetMinSize( wxSize( 400,-1 ) );
	
	wxBoxSizer* containerSizer = new wxBoxSizer( wxVERTICAL );
	
	m_AnimViewerSizer = new wxBoxSizer( wxVERTICAL );	
	
	containerSizer->Add( m_AnimViewerSizer, 1, wxALIGN_BOTTOM|wxEXPAND, 5 );
	
	wxBoxSizer* zoomScrollSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_sliderZoom = new wxSlider( this, wxID_ANY, 1, -500, 500, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	zoomScrollSizer->Add( m_sliderZoom, 1, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	containerSizer->Add( zoomScrollSizer, 0, wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	propsSizer->Add( containerSizer, 1, wxEXPAND, 5 );

    wxStaticBoxSizer* animSet = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Animations Set") ), wxVERTICAL );

	animSet->SetMinSize( wxSize( 150,-1 ) );
	m_stAnimList = new wxStaticText(  this, wxID_ANY, wxT("Animation List"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stAnimList->Wrap( -1 );
	animSet->Add( m_stAnimList, 0, wxLEFT, 5 );

	m_lbAnimList = new wxListBox(  this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_lbAnimList->SetMinSize( wxSize( 50,120 ) );

	animSet->Add( m_lbAnimList, 1, wxALL|wxEXPAND, 5 );

	m_ButtonNew = new wxButton( this, wxID_ANY, wxT("Create New"), wxDefaultPosition, wxDefaultSize, 0 );
	animSet->Add( m_ButtonNew, 0, wxALL|wxEXPAND, 5 );

	m_ButtonRemoveAnim = new wxButton( this, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	animSet->Add( m_ButtonRemoveAnim, 0, wxALL|wxEXPAND, 5 );

	propsSizer->Add( animSet, 0, wxALIGN_RIGHT|wxEXPAND, 5 );

	wxStaticBoxSizer* animPropsSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Animation Props") ), wxVERTICAL );

	animPropsSizer->SetMinSize( wxSize( 150,-1 ) );
	m_stFrames = new wxStaticText( this, wxID_ANY, wxT("Frames"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stFrames->Wrap( -1 );
	animPropsSizer->Add( m_stFrames, 0, wxLEFT, 5 );

	m_lbFrames = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_lbFrames->SetMinSize( wxSize( -1,120 ) );

	animPropsSizer->Add( m_lbFrames, 1, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* durationSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Duration, ms") ), wxHORIZONTAL );
	durationSizer->SetMinSize( wxSize( -1,25 ) );

	m_Duration = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 0 );
	m_Duration->SetMinSize( wxSize( -1,20 ) );
	durationSizer->Add( m_Duration, 1, wxALIGN_BOTTOM|wxALL, 5 );

	animPropsSizer->Add( durationSizer, 0, wxEXPAND, 5 );


	
	wxStaticBoxSizer* offsetSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Frame Offset") ), wxHORIZONTAL );
	
	offsetSizer->SetMinSize( wxSize( -1,25 ) );
	m_OffsetX = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -10000, 10000, 0 );
	m_OffsetX->SetMinSize( wxSize( 50,-1 ) );
	
	offsetSizer->Add( m_OffsetX, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_OffsetY = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -10000, 10000, 0 );
	m_OffsetY->SetMinSize( wxSize( 50,-1 ) );
	
	offsetSizer->Add( m_OffsetY, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	animPropsSizer->Add( offsetSizer, 0, wxEXPAND, 5 );
	
	m_cbShowBackFrame = new wxCheckBox( this, wxID_ANY, wxT("Show Back Frame"), wxDefaultPosition, wxDefaultSize, 0 );
	animPropsSizer->Add( m_cbShowBackFrame, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_ChooseFrame = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_ChooseFrame->Enable( false );
	animPropsSizer->Add( m_ChooseFrame, 0, wxALL|wxEXPAND, 5 );


	m_ButtonPlayAnim = new wxButton( this, wxID_ANY, wxT("Play/Stop anim"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	animPropsSizer->Add( m_ButtonPlayAnim, 0, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );

	m_ButtonRemoveFrame = new wxButton( this, wxID_ANY, wxT("Remove from list"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	animPropsSizer->Add( m_ButtonRemoveFrame, 0, wxALIGN_BOTTOM|wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );

	propsSizer->Add( animPropsSizer, 0, wxALIGN_RIGHT|wxEXPAND, 5 );

	m_MainSizer->Add( propsSizer, 1, wxEXPAND, 5 );


    
	
	wxBoxSizer* leftRightSizer = new wxBoxSizer( wxHORIZONTAL );

	leftRightSizer->SetMinSize( wxSize( -1,70 ) );
	m_ButtonLeft = new wxButton( m_Render.get(), wxID_ANY, wxT("<"), wxPoint(10, 10), wxSize( 20,60 ), 0 );
	//leftRightSizer->Add( m_ButtonLeft, 0, wxALIGN_BOTTOM|wxALL, 5 );

	m_FramesSizer = new wxBoxSizer( wxVERTICAL );

	//leftRightSizer->Add( m_FramesSizer, 1, wxALIGN_BOTTOM|wxALIGN_LEFT|wxEXPAND, 0 );

	m_ButtonRight = new wxButton( m_Render.get(), wxID_ANY, wxT(">"), wxDefaultPosition, wxSize( 20,60 ), 0 );
	//leftRightSizer->Add( m_ButtonRight, 0, wxALIGN_BOTTOM|wxALL, 5 );

	//m_MainSizer->Add( leftRightSizer, 0, wxALIGN_BOTTOM|wxALIGN_LEFT|wxALIGN_RIGHT|wxALIGN_TOP|wxALL|wxEXPAND|wxFIXED_MINSIZE, 5 );

    SetSizer(m_MainSizer);
	//m_Render->SetSizer( m_MainSizer );
	//m_Render->Layout();

	// menu
	/*m_MenuBar = new wxMenuBar( 0 );
    m_FileMenu = new wxMenu();

	wxMenuItem* item = new wxMenuItem(m_FileMenu, wxNewId(), "Open...", wxEmptyString, wxITEM_NORMAL);
	m_FileMenu->Append(item);

    m_MenuBar->Append(m_FileMenu, wxT("File")); */
}

void EdAtlasToolWndView::InstantiateRender()
{
    
    wxSize clientSize = GetClientSize();
    
    //int h = m_ToolBar->GetSize().GetHeight() + 22;


    wxPanel* renderpnl = new wxPanel(this);
	m_Render.reset(new WxIrrControl(renderpnl, wxID_ANY, wxPoint(0,10), wxSize(200, 200), 0, wxDefaultValidator, _T("AtlasToolControl")));
    wxButton* b = new wxButton(m_Render.get(), wxNewId(), _T("TestTEst"), wxPoint(10, 10), wxSize(100, 100));
    m_Render->Layout();

    //InitAnimEditor();

    m_Render->AttachOnWorkerInitDoneSignal(boost::bind(&EdAtlasToolWndView::SendOnShow, this));

    if (!m_Render->Init())
        wxMessageBox(wxT("Failed to initialize."), wxT("Error"), wxICON_ERROR);
    else
    {
        m_Render->Show();
        m_Render->Start();
    }
}

void EdAtlasToolWndView::AttachOnMouseEvents( AtlasToolLevel* lvl )
{
	m_Render->AttachOnMouseDownSignal(boost::bind(&AtlasToolLevel::OnMouseDown, lvl, _1, _2, _3));
	m_Render->AttachOnMouseUpSignal(boost::bind(&AtlasToolLevel::OnMouseUp, lvl, _1, _2, _3));
	m_Render->AttachOnMouseMovedSignal(boost::bind(&AtlasToolLevel::OnMouseMove, lvl, _1, _2));
	m_Render->AttachOnMouseDblClickSignal(boost::bind(&AtlasToolLevel::OnMouseDblClick, lvl, _1, _2, _3));
	m_Render->AttachMouseWheelSignal(boost::bind(&AtlasToolLevel::OnMouseWheel, lvl, _1, _2, _3, _4));
}

void EdAtlasToolWndView::PushLevelManager( CLevelManager* lmgr )
{
    if (m_Render)
        m_Render->PushLevelManager(lmgr);
}

void EdAtlasToolWndView::RefreshAnimationList(SpriteAnimationsList& animList)
{
	m_lbAnimList->Clear();
	for (uint i = 0; i < animList.size(); ++i)
	{
		m_lbAnimList->Append(animList[i].name.c_str());
	}
}

void EdAtlasToolWndView::RefreshFramesList(SpriteFramesListPtr framesList, core::array<int> indexes)
{
	m_lbFrames->Clear();
	for (uint i = 0; i < indexes.size(); ++i)
	{
		if (indexes[i] < (int)framesList->size())
			m_lbFrames->Append(framesList->get(indexes[i]).name.c_str());
	}
}

const core::position2df EdAtlasToolWndView::GetAnimViewerPos()
{
	if (m_AnimViewerSizer)
	{
		return core::position2df(m_AnimViewerSizer->GetPosition().x, m_AnimViewerSizer->GetPosition().y);
	}

	return core::position2df(0, 0);
}

const core::vector2di EdAtlasToolWndView::GetAnimViewerSize()
{
	if (m_AnimViewerSizer)
	{
		return core::vector2di(m_AnimViewerSizer->GetSize().GetWidth(), m_AnimViewerSizer->GetSize().GetHeight());
	}

	return core::vector2di(0, 0);
}

const core::position2df EdAtlasToolWndView::GetFramesBarPos()
{
	if (m_FramesSizer)
	{
		return core::position2df(m_FramesSizer->GetPosition().x, m_FramesSizer->GetPosition().y);
	}

	return core::position2df(0, 0);
}

const core::vector2di EdAtlasToolWndView::GetFramesBarSize()
{
	if (m_FramesSizer)
	{
		return core::vector2di(m_FramesSizer->GetSize().GetWidth(), m_FramesSizer->GetSize().GetHeight());
	}

	return core::vector2di(0, 0);
}

void EdAtlasToolWndView::SelectAnimation(u32 animation)
{
	if (animation >= 0 && animation < m_lbAnimList->GetCount())
	{
		m_lbAnimList->SetSelection(animation);
	}
}

void EdAtlasToolWndView::SelectFrame(u32 frameIndx, const FrameDef& frame)
{
	if (frameIndx >= 0 && frameIndx < m_lbFrames->GetCount())
	{
		m_lbFrames->SetSelection(frameIndx);
		m_Duration->SetValue(frame.animDuration);
		m_OffsetX->SetValue(frame.offsetX);
		m_OffsetY->SetValue(frame.offsetY);
	}
}

void EdAtlasToolWndView::ChangeCursor(int cursor)
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
