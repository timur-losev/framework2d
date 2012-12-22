#ifndef EdAtlasToolWndView_h__
#    define EdAtlasToolWndView_h__

#    include "IEdAtlasToolWndView.h"

#    include <wx/artprov.h>
#    include <wx/xrc/xmlres.h>
#    include <wx/string.h>
#    include <wx/dialog.h>
#    include <wx/gdicmn.h>
#    include <wx/font.h>
#    include <wx/colour.h>
#    include <wx/settings.h>
#    include "WxIrrControl.h"

#    include <wx/msgdlg.h>
#    include <wx/artprov.h>
#    include <wx/xrc/xmlres.h>
#    include <wx/string.h>
#    include <wx/button.h>
#    include <wx/gdicmn.h>
#    include <wx/font.h>
#    include <wx/colour.h>
#    include <wx/settings.h>
#    include <wx/sizer.h>
#    include <wx/stattext.h>
#    include <wx/listbox.h>
#    include <wx/statbox.h>
#    include <wx/spinctrl.h>
#    include <wx/panel.h>
#    include <wx/slider.h>
#    include <wx/wx.h>
#    include <wx/colordlg.h>

class EdAtlasToolWndView : public wxDialog, public IEdAtlasToolWndView
{
private:

    void					InitViewControl();
    void					DeInitViewControl();
    void					InitAnimEditor();
    void                                        InstantiateRender();
    WxIrrControl::Ptr                           m_Render;
    bool_t					m_IsResized;
    bool_t                                      m_IsShown;

protected:
    virtual void                        OnClose(wxCloseEvent & evt);
    virtual void			OnButtonClicked(wxCommandEvent & evt);
    virtual void			OnOpenFileClicked(wxCommandEvent & evt);
    virtual void			OnSaveFileClicked(wxCommandEvent & evt);
    virtual void			OnZoomScrolled(wxScrollEvent & evt);
    virtual void			OnAnimationSelected(wxCommandEvent & evt);
    virtual void			OnAnimationDurationChanged(wxCommandEvent & evt);
    virtual void			OnResizeWindow(wxSizeEvent & evt);
    virtual void			OnUpdate(wxCommandEvent & evt);
    void                                OnChangeBackgroundColor(wxCommandEvent& evt);

    virtual const char*                 DebugName() const
    {
        return "EdAtlasToolWndView";
    }

public:
    typedef boost::shared_ptr<EdAtlasToolWndView> Ptr;

public:
    EdAtlasToolWndView( wxWindow* parent,
                       wxWindowID id = wxID_ANY,
                       const wxString& title = wxEmptyString,
                       const wxPoint& pos = wxDefaultPosition,
                       const wxSize& size = wxSize( 800, 600 ),
                       long style = wxDEFAULT_DIALOG_STYLE | wxMAXIMIZE_BOX);
    ~EdAtlasToolWndView();

    void  PushLevelManager(CLevelManager* lmgr);
    void  RefreshAnimationList(SpriteAnimationsList& animList);
    void  RefreshFramesList(SpriteFramesListPtr framesList, core::array<int> indexes);
    void  SelectAnimation(u32 animation);
    void  SelectFrame(u32 frameIndx, const FrameDef& frame);
    void  MouseWheelZoom(int direction, int x, int y);
    void  ChangeCursor(int cursor);

    const core::position2df GetAnimViewerPos();
    const core::vector2di GetAnimViewerSize();
    const core::position2df GetFramesBarPos();
    const core::vector2di GetFramesBarSize();

    //wx overrides
    virtual bool                                Show( bool show = true );
    void                                        SendOnShow();

public:

    virtual void AttachOnMouseEvents(AtlasToolLevel* lvl);

private:
    wxToolBar*		m_ToolBar;
    wxMenuBar*      m_MenuBar;
    wxMenu*         m_FileMenu;
    wxSlider*		m_sliderZoom;
    wxStaticText*	m_stAnimList;
    wxListBox*		m_lbAnimList;
    wxButton*		m_ButtonNew;
    wxButton*		m_ButtonRemoveAnim;
    wxStaticText*	m_stFrames;
    wxListBox*		m_lbFrames;
    wxSpinCtrl*		m_Duration;
    wxButton*		m_ButtonPlayAnim;
    wxButton*		m_ButtonRemoveFrame;
    wxButton*		m_ButtonLeft;
    wxButton*		m_ButtonRight;
    wxBoxSizer*		m_AnimViewerSizer;
    wxBoxSizer*		m_FramesSizer;
    wxBoxSizer*		m_MainSizer;
    wxSpinCtrl*		m_OffsetX;
    wxSpinCtrl*		m_OffsetY;
    wxCheckBox*		m_cbShowBackFrame;
    wxComboBox*		m_ChooseFrame;
    wxCursor		m_SelectCursor;
    wxCursor		m_MoveCursor;
} ;

#endif // EdAtlasToolWndView_h__
