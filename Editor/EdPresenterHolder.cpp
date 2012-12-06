/*
 * File:   EdPresenterHolder.cpp
 * Author: Timur Losev aka void
 * Email: timur.losev@gmail.com
 * Created on February 6, 2012, 9:19 PM
 */

#include "EdPresenterHolder.h"
#include "EdViewHolder.h"

SINGLETON_SETUP(EdPresenterHolder);

EdPresenterHolder::EdPresenterHolder()
{
    SINGLETON_ENABLE_THIS;
}

EdPresenterHolder::~EdPresenterHolder()
{

}

void EdPresenterHolder::ShowMainWindow()
{
    EdViewHolder::getRef().ShowMainWindow();
}

void EdPresenterHolder::ShowAtlasToolDialog()
{
    EdViewHolder::getRef().ShowAtlasToolDialog();
}

void EdPresenterHolder::CreateGui()
{
    EdViewHolder::getRef().CreateGui();

    m_MainWnd.reset(new EdMainWndPresenter());
    m_AtlasToolWnd.reset(new EdAtlasToolWndPresenter());
    m_MappingWnd.reset(new EdMappingPresenter());
    m_SetNameDialog.reset(new EdSetNameForSelectionPresenter());
    m_SetValueDialog.reset(new EdSetValuePresenter());
}

void EdPresenterHolder::ShowMappingToolDialog()
{
    EdViewHolder::getRef().ShowMappingToolDialog(TRUE);
}

void EdPresenterHolder::ShowSetNameForSelectionDialog()
{
    EdViewHolder::getRef().ShowSetNameForSelectionDialog(TRUE);
}

void EdPresenterHolder::ShowSetValueDialog()
{
    EdViewHolder::getRef().ShowSetValueDialog(TRUE);
}
