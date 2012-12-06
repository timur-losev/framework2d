#include "EdSetNameForSelectionView.h"
#include <wx/msgdlg.h>
#include "CLogger.h"

EdSetNameForSelectionView::EdSetNameForSelectionView( wxWindow* parent, wxWindowID id /*= wxID_ANY*/,
                                                     const wxString& title /*= wxEmptyString*/, const wxPoint& pos /*= wxDefaultPosition*/,
                                                     const wxSize& size /*= wxSize( 200,100 )*/, long style /*= wxDEFAULT_DIALOG_STYLE */ )
                                                     :
wxDialog(parent, id, title, pos, size, style)
{
    InitViewControl();
}

EdSetNameForSelectionView::~EdSetNameForSelectionView()
{

}

boost::signals::connection EdSetNameForSelectionView::AttachOnOkSignal( const OnOkSignal::slot_type& slot )
{
    return m_OkSignal.connect(slot);
}

boost::signals::connection EdSetNameForSelectionView::AttachOnCancelSignal( const OnCancelSignal::slot_type& slot )
{
    return m_CancelSignal.connect(slot);
}

void EdSetNameForSelectionView::InitViewControl()
{
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxBoxSizer* bSizer = new wxBoxSizer( wxHORIZONTAL );

    m_TextCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    bSizer->Add( m_TextCtrl, 0, wxALL, 5 );

    m_OkButton = new wxButton( this, wxID_ANY, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer->Add( m_OkButton, 0, wxALL, 5 );

    m_CancelButton = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer->Add( m_CancelButton, 0, wxALL, 5 );

    this->SetSizer( bSizer );
    this->Layout();

    this->Centre( wxBOTH );

    m_CancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EdSetNameForSelectionView::OnCancelButtonClick), NULL, this );
    m_OkButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EdSetNameForSelectionView::OnOkButtonClick), NULL, this );
}

void EdSetNameForSelectionView::Close()
{
    wxDialog::Close();
}

void EdSetNameForSelectionView::OnCancelButtonClick( wxCommandEvent& event )
{
    m_CancelSignal();
}

void EdSetNameForSelectionView::OnOkButtonClick( wxCommandEvent& event )
{
    if (m_TextCtrl->GetValue().IsEmpty())
    {
        LogMessage(LOG_ERR, "Selection name could not be empty");
        event.Skip();
        return;
    }

    if (m_TextCtrl->GetValue().Find(_(" ")) != -1)
    {
        wxMessageBox("Remove spaces from the name.", "Please");
        LogMessage(LOG_ERR, "Remove spaces from the name.");
        event.Skip();
        return;
    }

    m_OkSignal((const char*)m_TextCtrl->GetValue().c_str());
}

void EdSetNameForSelectionView::Clear()
{
    m_OkSignal.disconnect_all_slots();
    m_CancelSignal.disconnect_all_slots();
    m_TextCtrl->Clear();
}

