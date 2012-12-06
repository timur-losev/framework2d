#ifndef EdSetValueView_h__
#define EdSetValueView_h__

#include "IEdSetValueView.h"

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

class EdSetValueView: public wxDialog, public IEdSetValueView
{
private:
    OnOkSignal      m_OkSignal;
    OnCancelSignal  m_CancelSignal;
    OnValueChangedSignal m_OnValueChangedSignal;

    void            InitViewControl();

    wxTextCtrl*     m_TextCtrl1;
    wxTextCtrl*     m_TextCtrl2;

    wxButton*       m_OkButton;
    wxButton*       m_CancelButton;

    core::stringc   m_RememberValue1;
    core::stringc   m_RememberValue2;
protected:
    virtual void    OnOkButtonClick( wxCommandEvent& event );
    virtual void    OnCancelButtonClick( wxCommandEvent& event );
    virtual void    OnTextValueChanged( wxCommandEvent& event );
public:
    EdSetValueView( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Set value"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400, 68), long style = wxDEFAULT_DIALOG_STYLE ); 
    virtual ~EdSetValueView();

    typedef boost::shared_ptr<EdSetValueView> Ptr;

    virtual boost::signals::connection	AttachOnOkSignal(const OnOkSignal::slot_type& slot);
    virtual boost::signals::connection	AttachOnCancelSignal(const OnCancelSignal::slot_type& slot);
    virtual boost::signals::connection	AttachValueChangedSignal(const OnValueChangedSignal::slot_type& slot);
    virtual void Values(const core::stringc& v1, const core::stringc& v2);
    virtual void Values(float v1, float v2);

    virtual void Close();
    virtual void Clear();
};


#endif // EdSetValueView_h__
