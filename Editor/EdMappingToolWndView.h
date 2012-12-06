#ifndef EDMAPPINGTOOLWNDVIEW_H__
#    define EDMAPPINGTOOLWNDVIEW_H__

#    include "IEdMappingToolWndView.h"
#    include "WxIrrControl.h"

#    include <wx/menu.h>
#    include <wx/dialog.h>
#    include <wx/artprov.h>
#    include <wx/xrc/xmlres.h>
#    include <wx/string.h>
#    include <wx/bitmap.h>
#    include <wx/image.h>
#    include <wx/icon.h>
#    include <wx/gdicmn.h>
#    include <wx/toolbar.h>
#    include <wx/font.h>
#    include <wx/colour.h>
#    include <wx/settings.h>
#    include <wx/sizer.h>
#    include <wx/scrolbar.h>
#    include <wx/stattext.h>
#    include <wx/listbox.h>
#    include <wx/bmpbuttn.h>
#    include <wx/button.h>
#    include <wx/statbox.h>
#    include <wx/panel.h>
#    include <wx/slider.h>
#    include <wx/colordlg.h>

class EdMappingToolWndView : public wxDialog, public IEdMappingToolWndView
{
    //*******************************************************************************
    //	WXWIDGETS
    //
    //*******************************************************************************
private:
    wxToolBar*							m_ToolBar;
    wxScrollBar*						m_scrollBarVertical;
    wxScrollBar*						m_ScrollBarHorizontal;
    wxStaticText*						m_stMapList;
    wxStaticText*						m_stTextureList;
    wxListBox*							m_lbMapList;
    wxListBox*							m_lbTextureList;
    wxButton*							m_ButtonAddFrame;
    wxButton*							m_ButtonShowHideAll;
    wxButton*							m_ButtonRemoveFrame;
    wxMenu*							m_lbMapListPopup;
    wxBoxSizer*							m_ViewerSizer;
    wxSlider*							m_sliderZoom;
    wxCursor							m_SelectCursor;
    wxCursor							m_MoveCursor;
    wxButton*							m_ButtonAddTexture;
    wxButton*							m_ButtonRemoveTexture;

protected:
    //wx handlers
    virtual void						OnClose(wxCloseEvent & evt);
    virtual void						OnOpenImage(wxCommandEvent& evt);
    virtual void						OnOpenMappingFile(wxCommandEvent& evt);
    virtual void						OnClearSelections(wxCommandEvent& evt);
    virtual void						OnSaveToFile(wxCommandEvent& evt);
    virtual void						ListBoxOnContextMenu(wxMouseEvent &evt);
    virtual void						SetNameOnMenuSelection(wxCommandEvent& evt);
    virtual void						OnZoomScrolled(wxScrollEvent & evt);
    virtual void						OnButtonClicked(wxCommandEvent & evt);
    virtual void						OnResizeWindow(wxSizeEvent & evt);
    virtual void						OnUpdate(wxCommandEvent & evt);
    virtual void						OnListBoxSelected(wxCommandEvent & evt);
    void							RemoveFrame(wxCommandEvent & evt);
    void							RemoveTexture(wxCommandEvent & evt);
    void							OnSelectFrameList(wxCommandEvent & evt);
    void							OnChangeBackgroundColor(wxCommandEvent& evt);

    virtual const char*                                         DebugName() const
    {
        return "EdMappingToolWndView";
    }


    //*******************************************************************************
    //	SIGNALS
    //
    //*******************************************************************************
private:
    void InstantiateRender();
public:
    virtual void						AttachOnMouseEvents(MappingToolLevel* lvl);


public:
    EdMappingToolWndView(wxWindow* parent,
                         wxWindowID id = wxID_ANY,
                         const wxString& title = wxEmptyString,
                         const wxPoint& pos = wxDefaultPosition,
                         const wxSize& size = wxSize(800, 600),
                         long style = wxDEFAULT_DIALOG_STYLE | wxMAXIMIZE_BOX);
    virtual ~EdMappingToolWndView(void);

    void							PushLevelManager(CLevelManager* lmgr);
    virtual void						RefreshFramesList(const SpriteFramesListPtr& frames);
    virtual void						RefreshTexturesList(const SpriteTexturesNamesListPtr& names);
    virtual void						MouseWheelZoom(int direction, int x, int y);
    virtual const core::position2df                             GetMapViewerPos();
    virtual const core::vector2di                               GetMapViewerSize();
    virtual int							GetSelectedFrameIndex();
    virtual void						ChangeCursor(int cursor);

    virtual bool                                                Show( bool show = true );
    void                                                        SendOnShow();

public:
    typedef boost::shared_ptr<EdMappingToolWndView> Ptr;

private:
    void							InitViewControl();
    void							ClearSelections();

    WxIrrControl::Ptr                                           m_Render;
    bool_t							m_IsResized;

} ;

#endif // EDMAPPINGTOOLWNDVIEW_H__
