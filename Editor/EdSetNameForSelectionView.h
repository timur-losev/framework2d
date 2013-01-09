#ifndef EdSetNameForSelectionView_h__
#define EdSetNameForSelectionView_h__

#include "IEdSetNameForSelectionView.h"

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

class EdSetNameForSelectionView: public wxDialog, public IEdSetNameForSelectionView
{
private:
    OnOkSignal      m_OkSignal;
    OnCancelSignal  m_CancelSignal;

    void            InitViewControl();


    wxTextCtrl*     m_TextCtrl;
    wxButton*       m_OkButton;
    wxButton*       m_CancelButton;
protected:
    virtual void    OnOkButtonClick( wxCommandEvent& event );
    virtual void    OnCancelButtonClick( wxCommandEvent& event );
public:
    EdSetNameForSelectionView( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Set name"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(294,68), long style = wxDEFAULT_DIALOG_STYLE ); 
    virtual ~EdSetNameForSelectionView();

    typedef boost::shared_ptr<EdSetNameForSelectionView> Ptr;

    virtual boost::signals::connection	AttachOnOkSignal(const OnOkSignal::slot_type& slot);
    virtual boost::signals::connection	AttachOnCancelSignal(const OnCancelSignal::slot_type& slot);

    virtual void Close();
    virtual void Clear();
};

#endif // EdSetNameForSelectionView_h__
