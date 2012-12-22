/*
 * File:   EdViewHolder.cpp
 * Author: Timur Losev aka void
 * Email: timur.losev@gmail.com
 * Created on February 6, 2012, 12:52 AM
 */

#include "EdViewHolder.h"
#include "EdMainWndView.h"
#include "EdAtlasToolWndView.h"
#include "EdMappingToolWndView.h"
#include "EdSetNameForSelectionView.h"
#include "EdSetValueView.h"

class EdViewHolderImpl
{
private:
    EdMainWndView::Ptr      m_MainWnd;
    EdAtlasToolWndView::Ptr m_AtlasToolDlg;
    EdMappingToolWndView::Ptr m_MappingToolDlg;
    EdSetNameForSelectionView::Ptr m_SetNameForSelectionDlg;
    EdSetValueView::Ptr     m_SetValueDlg;
public:

    void CreateGui()
    {
        m_MainWnd.reset(new EdMainWndView(0));
        m_AtlasToolDlg.reset(new EdAtlasToolWndView(m_MainWnd.get()));
        m_MappingToolDlg.reset(new EdMappingToolWndView(m_MainWnd.get()));
        m_SetNameForSelectionDlg.reset(new EdSetNameForSelectionView(m_MappingToolDlg.get())); //TODO: Make setting a parent in real time mode
        m_SetValueDlg.reset(new EdSetValueView(m_MainWnd.get()));
    }

    EdMainWndView::Ptr  MainWindow()
    {
        return m_MainWnd;
    }

    EdAtlasToolWndView::Ptr AtlasTool()
    {
        return m_AtlasToolDlg;
    }

    EdMappingToolWndView::Ptr MappingTool()
    {
        return m_MappingToolDlg;
    }

    EdSetNameForSelectionView::Ptr SetNameForSelection()
    {
        return m_SetNameForSelectionDlg;
    }

    EdSetValueView::Ptr SetValueDialog()
    {
        return m_SetValueDlg;
    }
};

static EdViewHolderImpl* pImpl;

SINGLETON_SETUP(EdViewHolder);

EdViewHolder::EdViewHolder()
{
    SINGLETON_ENABLE_THIS;

    pImpl = new EdViewHolderImpl();
}

EdViewHolder::~EdViewHolder()
{
    APP_API_DEL(pImpl);
}

void EdViewHolder::CreateGui()
{
    pImpl->CreateGui();
}

IEdMainWndView::Ptr	EdViewHolder::MainWindow()
{
    return pImpl->MainWindow();
}

void EdViewHolder::ShowMainWindow()
{
    pImpl->MainWindow()->Show();
}

IEdAtlasToolWndView::Ptr EdViewHolder::AtlasToolDialog()
{
    return pImpl->AtlasTool();
}

void EdViewHolder::ShowAtlasToolDialog(bool_t showmodal)
{
    if (showmodal)
        pImpl->AtlasTool()->ShowModal();
    else
        pImpl->AtlasTool()->Show();
}

IEdMappingToolWndView::Ptr EdViewHolder::MappingToolDialog()
{
    return pImpl->MappingTool();
}

void EdViewHolder::ShowMappingToolDialog( bool_t showmodal /*= FALSE*/ )
{
    if (showmodal)
        pImpl->MappingTool()->ShowModal();
    else
        pImpl->MappingTool()->Show();
}

IEdSetNameForSelectionView::Ptr EdViewHolder::SetNameForSelectionDialog()
{
    return pImpl->SetNameForSelection();
}

void EdViewHolder::ShowSetNameForSelectionDialog( bool_t showmodal /*= FALSE*/ )
{
    if (showmodal)
        pImpl->SetNameForSelection()->ShowModal();
    else
        pImpl->SetNameForSelection()->Show();
}

IEdSetValueView::Ptr EdViewHolder::SetValueDialog()
{
    return pImpl->SetValueDialog();
}

void EdViewHolder::ShowSetValueDialog( bool_t showmodal /*= FALSE*/ )
{
    if (showmodal)
        pImpl->SetValueDialog()->ShowModal();
    else
        pImpl->SetValueDialog()->Show();
}









