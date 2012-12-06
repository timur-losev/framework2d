#include "EdSetValueView.h"
#include <wx/msgdlg.h>
#include "CLogger.h"

EdSetValueView::EdSetValueView( wxWindow* parent, wxWindowID id /*= wxID_ANY*/,
                                                     const wxString& title /*= wxEmptyString*/, const wxPoint& pos /*= wxDefaultPosition*/,
                                                     const wxSize& size /*= wxSize( 200,100 )*/, long style /*= wxDEFAULT_DIALOG_STYLE */ )
                                                     :
wxDialog(parent, id, title, pos, size, style)
{
    InitViewControl();
}

EdSetValueView::~EdSetValueView()
{

}

boost::signals::connection EdSetValueView::AttachOnOkSignal( const OnOkSignal::slot_type& slot )
{
    return m_OkSignal.connect(slot);
}

boost::signals::connection EdSetValueView::AttachOnCancelSignal( const OnCancelSignal::slot_type& slot )
{
    return m_CancelSignal.connect(slot);
}

void EdSetValueView::InitViewControl()
{
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxBoxSizer* bSizer = new wxBoxSizer( wxHORIZONTAL );

    m_TextCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    bSizer->Add( m_TextCtrl1, 0, wxALL, 5 );

    m_TextCtrl2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    bSizer->Add( m_TextCtrl2, 0, wxALL, 5 );

    m_OkButton = new wxButton( this, wxID_ANY, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer->Add( m_OkButton, 0, wxALL, 5 );

    m_CancelButton = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer->Add( m_CancelButton, 0, wxALL, 5 );

    this->SetSizer( bSizer );
    this->Layout();

    this->Centre( wxBOTH );

    m_CancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EdSetValueView::OnCancelButtonClick), NULL, this );
    m_OkButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EdSetValueView::OnOkButtonClick), NULL, this );
    m_TextCtrl1->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( EdSetValueView::OnTextValueChanged ), NULL, this );
    m_TextCtrl2->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( EdSetValueView::OnTextValueChanged ), NULL, this );
}

void EdSetValueView::Close()
{
    wxDialog::Close();
}

void EdSetValueView::OnCancelButtonClick( wxCommandEvent& event )
{
    m_CancelSignal();

    m_OnValueChangedSignal(m_RememberValue1, m_RememberValue2);
}

void EdSetValueView::OnOkButtonClick( wxCommandEvent& event )
{
    core::stringc str1 = (const char*)m_TextCtrl1->GetValue().c_str();
    core::stringc str2 = (const char*)m_TextCtrl2->GetValue().c_str();
    m_OkSignal(str1, str2);
}

void EdSetValueView::Clear()
{
    //m_OkSignal.disconnect_all_slots();
    //m_CancelSignal.disconnect_all_slots();
    m_OnValueChangedSignal.disconnect_all_slots();
    m_TextCtrl1->Clear();
    m_TextCtrl2->Clear();
    m_TextCtrl2->Enable(true);
}

void EdSetValueView::Values( const core::stringc& v1, const core::stringc& v2 )
{
    m_TextCtrl1->SetValue(v1.c_str());
    m_TextCtrl2->SetValue(v2.c_str());

    if (v2.empty())
        m_TextCtrl2->Enable(false);

    m_RememberValue1 = v1;
    m_RememberValue2 = v2;
}

void EdSetValueView::Values( float v1, float v2 )
{
    Values(core::stringc(v1), core::stringc(v2));
}

boost::signals::connection EdSetValueView::AttachValueChangedSignal( const OnValueChangedSignal::slot_type& slot )
{
    return m_OnValueChangedSignal.connect(slot);
}

void EdSetValueView::OnTextValueChanged( wxCommandEvent& event )
{
    core::stringc str1 = (const char*)m_TextCtrl1->GetValue().c_str();
    core::stringc str2 = (const char*)m_TextCtrl2->GetValue().c_str();
    m_OnValueChangedSignal(str1, str2);
}

