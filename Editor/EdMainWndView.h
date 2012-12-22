/*
 * File:   EdMainWndView.h
 * Author: void
 *
 * Created on February 6, 2012, 12:20 AM
 */

#ifndef EDMAINWNDVIEW_H
#    define	EDMAINWNDVIEW_H

#include "IEdMainWndView.h"
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/treectrl.h>
#include <wx/filedlg.h>
#include "WxIrrControl.h"

class EdMainWndView:  public wxFrame, public IEdMainWndView
{
private:
    struct SMenuItem	// Main menu item
    {
        SMenuItem(const wxString& name, size_t _key)
            :
                strname(name),
                key(_key) {}

        wxString                    strname;
        size_t                      key;
    };

    typedef std::map<long, SMenuItem*> MenuItem;

    class PropertiesTreeItemData: public wxTreeItemData
    {
    private:
        EPropertiesTags m_Tag;
    public:
        PropertiesTreeItemData(EPropertiesTags tag): m_Tag(tag) {}
        EPropertiesTags GetTag() const { return m_Tag; }
    };

private:
    wxPanel*						m_RenderPanel;
    WxIrrControl::Ptr				m_Control;
    wxStatusBar*					m_StatusBar;
    wxMenuBar*						m_MenuBar;
    wxMenu*							m_FileMenu;
    wxMenu*							m_ToolsMenu;

    wxNotebook*						m_Tools;
    wxPanel*						m_ConstructTools;
    wxPanel*						m_Properties;
    wxPanel*						m_ElementsList;
    wxTreeCtrl*						m_ConstructToolTree;
    wxTreeCtrl*						m_ElementsTree;
    wxTreeCtrl*                                         m_GameObjectsProperties;

    MenuItem						m_MenuItems;
private:
    void							InitViewControl();
    void							FillMenuItems();

    //wx events
    virtual void					OnMenuItemSelected(wxCommandEvent& evt);
    virtual void					OnSaveLevelSelected(wxCommandEvent& evt);
    virtual void					OnLoadLevelSelected(wxCommandEvent& evt);
    virtual void					OnLoadMappingFile_in_contruct_tool(wxCommandEvent& evt);
    virtual void					OnNewStaticObject_in_elements_list(wxCommandEvent& evt);
    virtual void					OnNewAnimatedObject_in_elements_list(wxCommandEvent& evt);
    virtual void					OnContructToolTreeItemActivated( wxTreeEvent& event );
    virtual void					OnElementsTreeItemActivated( wxTreeEvent& event );
    virtual void					OnGameObjectPropertiesTreeItemActivated( wxTreeEvent& event );


    //other events
public:
    typedef boost::shared_ptr<EdMainWndView> Ptr;

    EdMainWndView(wxWindow* parent, wxWindowID id = -1);
    virtual ~EdMainWndView();

    virtual void					PushLevelManager(CLevelManager* lmgr);
    virtual MultipleConnections_t                       AttachOnMouseEvents(EditablePagedLevel* lvl);
    virtual MultipleConnections_t                       AttachOnKeyEvents(EditablePagedLevel* lvl);
    virtual void					RefreshConstructNodes(const ConstructNodes_t& nodes);
    virtual void					RefreshElementsNodes(const ElementsNodes_t& nodes);
    virtual void					ReadPropertiesFromObject(GameObject::Ptr obj);
    virtual void					MarkSelectedObjectInElementsTree(GameObject::Ptr obj);

    void                                                OnShow(wxShowEvent& event);
protected:
    virtual const char*				DebugName() const { return "EdMainWndView"; }
} ;

#endif	/* EDMAINWNDVIEW_H */

