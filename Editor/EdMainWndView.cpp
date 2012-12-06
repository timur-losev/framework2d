/*
* File:   EdMainWndView.cpp
* Author: void
*
* Created on February 6, 2012, 12:20 AM
*/

#include "EdMainWndView.h"
#include <wx/settings.h>
#include <wx/msgdlg.h>
#include "LevelManager.h"
#include "EditablePagedLevel.h"
#include "EdViewHolder.h"

#include "CLogger.h"

// just for view info
#include "StaticGameObject.h"
#include "AnimatedGameObject.h"

EdMainWndView::EdMainWndView(wxWindow* parent, wxWindowID id)
{
    Create(parent, id, _T("Editor main window"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    //SetClientSize(wxSize(1024,768));

	Maximize();

    InitViewControl();
}

void EdMainWndView::InitViewControl()
{
    wxPanel* canvas = new wxPanel(this, wxNewId(), wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    canvas->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNSHADOW));

	m_RenderPanel = new wxPanel(canvas, wxNewId(), wxDefaultPosition, wxSize(960,480), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    m_Control.reset(new WxIrrControl(m_RenderPanel, wxID_ANY, wxDefaultPosition, wxSize(960,480), 0, wxDefaultValidator, _T("MainWindowControl")));

    m_Tools = new wxNotebook(canvas, wxNewId(), wxPoint( 1000 ,10), wxSize(300, 800), 0, _T("ToolsPanel"));

    m_ElementsList = new wxPanel(m_Tools, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    m_Tools->AddPage(m_ElementsList, _("Elements list"), true);

    wxButton* newStaticObjectButton = new wxButton(m_ElementsList, wxNewId(), _("New static object"), wxPoint(3, 3), wxSize(100, 20));
    wxButton* newAnimatedObjectButton = new wxButton(m_ElementsList, wxNewId(), _("New animated object"), wxPoint(106, 3), wxSize(100, 20));

    m_ElementsTree = new wxTreeCtrl( m_ElementsList, wxID_ANY, wxPoint(3, 26), wxSize(280 ,750), wxTR_DEFAULT_STYLE );
    m_ElementsTree->Connect(wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( EdMainWndView::OnElementsTreeItemActivated), NULL, this );
    newStaticObjectButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EdMainWndView::OnNewStaticObject_in_elements_list), NULL, this);
    newAnimatedObjectButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EdMainWndView::OnNewAnimatedObject_in_elements_list), NULL, this);

    m_ConstructTools = new wxPanel(m_Tools, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    m_Tools->AddPage(m_ConstructTools, _("Contruct"), false);

    m_Properties = new wxPanel(m_Tools, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    m_Tools->AddPage(m_Properties, _("Properties"), false);

    wxButton* loadMappingButton = new wxButton(m_ConstructTools, wxNewId(), _("Load mapping"), wxPoint(3, 3), wxSize(100, 20));

    loadMappingButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EdMainWndView::OnLoadMappingFile_in_contruct_tool), NULL, this);
    m_ConstructToolTree = new wxTreeCtrl( m_ConstructTools, wxID_ANY, wxPoint(3, 26), wxSize(280 ,750), wxTR_DEFAULT_STYLE );
    m_ConstructToolTree->Connect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( EdMainWndView::OnContructToolTreeItemActivated ), NULL, this );

    m_GameObjectsProperties = new wxTreeCtrl( m_Properties, wxID_ANY, wxPoint(3, 26), wxSize(280 ,750), wxTR_DEFAULT_STYLE );
    m_GameObjectsProperties->Connect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( EdMainWndView::OnGameObjectPropertiesTreeItemActivated ), NULL, this );

    m_StatusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
    m_MenuBar = new wxMenuBar( 0 );
    m_FileMenu = new wxMenu();
    m_ToolsMenu = new wxMenu();

    FillMenuItems();

    m_MenuBar->Append(m_FileMenu, wxT("File")); 
    m_MenuBar->Append(m_ToolsMenu, wxT("Tools"));

    SetMenuBar( m_MenuBar );

    Connect(wxEVT_SHOW, wxShowEventHandler(EdMainWndView::OnShow));
}

EdMainWndView::~EdMainWndView()
{
    m_Control->Close();
    m_Control.reset();
}

void EdMainWndView::FillMenuItems()
{
    std::vector<SMenuItem*> fileMenuNames;

    fileMenuNames.push_back(new SMenuItem(wxString(wxT("New level")), IEdMainWndView::ES_ON_NEW_LEVEL_SELECTED));
    fileMenuNames.push_back(new SMenuItem(wxString(wxT("New page")), IEdMainWndView::ES_ON_NEW_PAGE_SELECTED));
    fileMenuNames.push_back(new SMenuItem(wxString(wxT("Exit")), IEdMainWndView::ES_ON_EXIT_SELECTED));

    std::vector<SMenuItem*> toolsMenuNames;
    toolsMenuNames.push_back(new SMenuItem(wxString(wxT("Atlas tools")), IEdMainWndView::ES_ON_ATLAS_TOOL_SELECTED));
    toolsMenuNames.push_back(new SMenuItem(wxString(wxT("Mapping")), IEdMainWndView::ES_ON_MAPPING_SELECTED));

    uint i = 0;
    for (; i < fileMenuNames.size(); ++i)
    {
        long id = wxNewId();
        SMenuItem* mitem = fileMenuNames[i];
        wxMenuItem* item = new wxMenuItem(m_FileMenu, id, mitem->strname, wxEmptyString, wxITEM_NORMAL);
        m_FileMenu->Append(item);
        Connect(id, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(EdMainWndView::OnMenuItemSelected));
        m_MenuItems[id] = mitem;
    }

    for (i = 0 ; i < toolsMenuNames.size(); ++i)
    {
        long id = wxNewId();
        SMenuItem* mitem = toolsMenuNames[i];
        wxMenuItem* item = new wxMenuItem(m_ToolsMenu, id, mitem->strname, wxEmptyString, wxITEM_NORMAL);
        m_ToolsMenu->Append(item);
        Connect(id, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(EdMainWndView::OnMenuItemSelected));
        m_MenuItems[id] = mitem;
    }

    long saveLevelId = wxNewId();
    wxMenuItem* saveLevelItem = new wxMenuItem(m_FileMenu, saveLevelId, _("Save Level"), wxEmptyString, wxITEM_NORMAL);
    m_FileMenu->Insert(3, saveLevelItem);
    Connect(saveLevelId, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(EdMainWndView::OnSaveLevelSelected));

    long loadLevelId = wxNewId();
    wxMenuItem* loadLevelItem = new wxMenuItem(m_FileMenu, loadLevelId, _("Load Level"), wxEmptyString, wxITEM_NORMAL);
    m_FileMenu->Insert(4, loadLevelItem);
    Connect(loadLevelId, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(EdMainWndView::OnLoadLevelSelected));
}

void EdMainWndView::OnShow(wxShowEvent& event)
{
    if (!m_Control->IsInitilized())
    {
        if (!m_Control->Init())
            wxMessageBox(wxT("Failed to initialize."), wxT("Error"), wxICON_ERROR);
        else
        {
            m_Control->Show();
            m_Control->Start();
        }
    }
    //event.Skip();
}

void EdMainWndView::PushLevelManager( CLevelManager* lmgr )
{
    if (m_Control)
        m_Control->PushLevelManager(lmgr);
}

IEdMainWndView::MultipleConnections_t EdMainWndView::AttachOnMouseEvents( EditablePagedLevel* lvl )
{
    IEdMainWndView::MultipleConnections_t lst;

    lst.push_back(m_Control->AttachOnMouseDownSignal(boost::bind(&EditablePagedLevel::OnMouseDown, lvl, _1, _2, _3)));
    lst.push_back(m_Control->AttachOnMouseUpSignal(boost::bind(&EditablePagedLevel::OnMouseUp, lvl, _1, _2, _3)));
    lst.push_back(m_Control->AttachOnMouseMovedSignal(boost::bind(&EditablePagedLevel::OnMouseMove, lvl, _1, _2)));

    return lst;
}

IEdMainWndView::MultipleConnections_t EdMainWndView::AttachOnKeyEvents( EditablePagedLevel* lvl )
{
    IEdMainWndView::MultipleConnections_t lst;

    lst.push_back(m_Control->AttachOnKeyDownSignal(boost::bind(&EditablePagedLevel::OnKeyDown, lvl, _1)));

    return lst;
}

void EdMainWndView::RefreshConstructNodes( const ConstructNodes_t& nodes )
{
    m_ConstructToolTree->DeleteAllItems();
    wxTreeItemId root = m_ConstructToolTree->AddRoot(_("Contruct Nodes"));

    ConstructNodes_t::Iterator iter = nodes.getIterator();

    while(!iter.atEnd())
    {
        core::stringc keyitem = iter.getNode()->getKey();
        wxTreeItemId mpfitem = m_ConstructToolTree->AppendItem(root, keyitem.c_str());

        const SpriteFramesListPtr& sels = iter.getNode()->getValue();
        for (size_t i = 0; i < sels->size(); ++i)
        {
            const FrameDef& entry = sels->get(i);
            std::ostringstream ss;

            ss << entry.name.c_str() << " " << entry.x <<","<<entry.y <<","\
                << entry.width <<","<< entry.height;
            m_ConstructToolTree->AppendItem(mpfitem, ss.str().c_str());
        }

        iter++;
    }
}

void EdMainWndView::RefreshElementsNodes( const ElementsNodes_t& nodes )
{
    m_ElementsTree->DeleteAllItems();
    wxTreeItemId root = m_ElementsTree->AddRoot(_("Elements"));

    ElementsNodes_t::Iterator iter = nodes.getIterator();

    while(!iter.atEnd())
    {
        core::stringc objName = iter.getNode()->getKey();
        wxTreeItemId objitemid = m_ElementsTree->AppendItem(root, objName.c_str());
        GameObject::Ptr gobj = iter.getNode()->getValue();

        switch (gobj->Type())
        {
        case GameObject::ET_STATIC:
            {

                StaticGameObject::Ptr stobj = gobj->AsStaticGameObject();

                const StaticGameObject::GraphicState_t& grstate = stobj->GraphicState();
                if (grstate.empty())
                {
                    m_ElementsTree->AppendItem(objitemid, _("Empty object"));
                    break;
                }

                StaticGameObject::GraphicStateIter_t end = grstate.end();
                for (StaticGameObject::GraphicStateIter_t i = grstate.begin(); end != i; ++i)
                {
                    m_ElementsTree->AppendItem(objitemid, wxString(_("mpe: ")) + wxString((*i).m_FrameInfo.name.c_str()));
                }
            }
            break;

        case GameObject::ET_ANIMATED:
            {
                //TODO
            }
            break;
        }

        iter++;
    }
}

void EdMainWndView::ReadPropertiesFromObject( GameObject::Ptr obj )
{
    m_GameObjectsProperties->DeleteAllItems();

    if (!obj) return;

    wxTreeItemId root = m_GameObjectsProperties->AddRoot(obj->Name().c_str());

    wxTreeItemId positem = m_GameObjectsProperties->AppendItem(root, _("Position"));
    std::ostringstream ss;
    ss << "X:" << obj->Position().X << " Y: " << obj->Position().Y;
    wxTreeItemId posXYitem = m_GameObjectsProperties->AppendItem(positem, ss.str(), -1, -1, new PropertiesTreeItemData(EPT_POSITION));
    ss.str("");

    wxTreeItemId rotitem = m_GameObjectsProperties->AppendItem(root, _("Rotation"));
    ss << "Degrees: " << obj->Rotation();
    wxTreeItemId rotDegreeItem = m_GameObjectsProperties->AppendItem(rotitem, ss.str(), -1, -1, new PropertiesTreeItemData(EPT_ROTATION));
    ss.str("");

    wxTreeItemId scaleitem = m_GameObjectsProperties->AppendItem(root, _("Scale"));
    ss << "X:" << obj->Scale().X << " Y: " << obj->Scale().Y;
    wxTreeItemId scaleXYItem = m_GameObjectsProperties->AppendItem(scaleitem, ss.str(), -1, -1, new PropertiesTreeItemData(EPT_SCALE));
    ss.str("");

    wxTreeItemId nameitem = m_GameObjectsProperties->AppendItem(root, _("Name"));
    ss << "String: " << obj->Name().c_str();
    wxTreeItemId nameStringItem = m_GameObjectsProperties->AppendItem(nameitem, ss.str(), -1, -1, new PropertiesTreeItemData(EPT_NAME));
    ss.str("");
}

void EdMainWndView::MarkSelectedObjectInElementsTree( GameObject::Ptr obj )
{
    if (!obj)
    {
        m_ElementsTree->UnselectAll();
        return;
    }

    wxTreeItemId root = m_ElementsTree->GetRootItem();

    if (root.IsOk())
    {
        wxTreeItemIdValue cookie;
        wxTreeItemId item = m_ElementsTree->GetFirstChild( root, cookie );

        while(item.IsOk())
        {
            wxString text = m_ElementsTree->GetItemText(item);
            if (text.CompareTo(obj->Name().c_str()) == 0)
            {
                m_ElementsTree->SelectItem(item, true);
                m_ElementsTree->Expand(item);
                break;
            }

            item = m_ElementsTree->GetNextChild(item, cookie);
        }
    }
}

#include "EdMainWindowWxEvents.hpp"
