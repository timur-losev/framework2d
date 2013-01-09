
#include "IEdSetNameForSelectionView.h"

void EdMainWndView::OnLoadMappingFile_in_contruct_tool( wxCommandEvent& evt )
{
    wxFileDialog dlg(this, _("Choose a mapping file to open"), wxEmptyString, wxEmptyString, _("Mapping file (*.mpf)|*.mpf|All Files (*.*)|*.*"), wxFD_OPEN, wxDefaultPosition);

    if (dlg.ShowModal() == wxID_OK)
    {
        wxString filenp = dlg.GetPath();

        io::path txtpath = (const fschar_t*)filenp.c_str();

        CallBack(IEdMainWndView::ES_ON_LOAD_MAPPING_FILE, txtpath);
    }

    dlg.Destroy();

    evt.Skip();
}

void EdMainWndView::OnMenuItemSelected(wxCommandEvent& evt)
{
    long id = evt.GetId();

    MenuItem::const_iterator iter = m_MenuItems.find(id);
    APP_API_ASSERT(iter != m_MenuItems.end());

    CallBack(iter->second->key);
}

void EdMainWndView::OnContructToolTreeItemActivated( wxTreeEvent& evt )
{
    wxTreeItemId item = evt.GetItem();
    wxTreeItemId parent = m_ConstructToolTree->GetItemParent(item);

    if (!parent.IsOk() || parent == m_ConstructToolTree->GetRootItem())
    {
        evt.Skip();
        return;
    }

    wxString mpfitem = m_ConstructToolTree->GetItemText(parent);
    wxString subitemtext = m_ConstructToolTree->GetItemText(item);

    LogDebug("mpf item text = " << mpfitem<< \
        " subitem text = " << subitemtext);

    //find first space and extract substring before it
    core::stringc subitemname = (const char*)subitemtext.SubString(0, (size_t)(subitemtext.Find(_(" ")) - 1)).c_str();
    core::stringc mpfitem_ = (const char*)mpfitem.c_str();
    CallBack(IEdMainWndView::ES_ON_TREE_ITEM_SELECTED, mpfitem_, subitemname);
}

void EdMainWndView::OnElementsTreeItemActivated( wxTreeEvent& evt )
{
    wxTreeItemId selectedItem = evt.GetItem();
    wxTreeItemId root = m_ElementsTree->GetRootItem();
    wxTreeItemId parent = m_ElementsTree->GetItemParent(selectedItem);

    if (!parent.IsOk() || parent != root)
    {
        evt.Skip();
        return;
    }

    wxString selectedGameObjectName = m_ElementsTree->GetItemText(selectedItem);
    LogDebug("Selected game object name = " << selectedGameObjectName);
    CallBack(IEdMainWndView::ES_ON_GAME_OBJECT_SELECTED, core::stringc((const char*)selectedGameObjectName.c_str()));
}

void EdMainWndView::OnNewStaticObject_in_elements_list( wxCommandEvent& evt )
{
    CallBack(IEdMainWndView::ES_ON_ADD_NEW_STATIC_OBJECT);
}

void EdMainWndView::OnNewAnimatedObject_in_elements_list(wxCommandEvent& evt)
{
    CallBack(IEdMainWndView::ES_ON_ADD_NEW_ANIMATED_OBJECT);
}

void EdMainWndView::OnGameObjectPropertiesTreeItemActivated( wxTreeEvent& evt )
{
    wxTreeItemId item = evt.GetItem();

    if (!item.IsOk()) return;

    PropertiesTreeItemData* data = (PropertiesTreeItemData*)m_GameObjectsProperties->GetItemData(item);
    if (!data) return;

    CallBack(IEdMainWndView::ES_ON_GAME_OBJECT_PROPERTY_SELECTED, data->GetTag());
}

void EdMainWndView::OnSaveLevelSelected( wxCommandEvent& evt )
{
    wxFileDialog dlg(this, _("Save current level"), wxEmptyString, wxEmptyString, _("Level file (*.lvl)|*.lvl|All Files (*.*)|*.*"), wxFD_SAVE, wxDefaultPosition);

    if (dlg.ShowModal() == wxID_OK)
    {
        wxString filenp = dlg.GetPath();

        io::path txtpath = (const fschar_t*)filenp.c_str();

        CallBack(IEdMainWndView::ES_ON_SAVE_LEVEL_SELECTED, txtpath);
    }

    dlg.Destroy();
}


void EdMainWndView::OnLoadLevelSelected( wxCommandEvent& evt )
{
    wxFileDialog dlg(this, _("Load level"), wxEmptyString, wxEmptyString, _("Level file (*.lvl)|*.lvl|All Files (*.*)|*.*"), wxFD_OPEN, wxDefaultPosition);

    if (dlg.ShowModal() == wxID_OK)
    {
        wxString filenp = dlg.GetPath();

        io::path txtpath = (const fschar_t*)filenp.c_str();

        CallBack(IEdMainWndView::ES_ON_LOAD_LEVEL_SELECTED, txtpath);
    }

    dlg.Destroy();
}


