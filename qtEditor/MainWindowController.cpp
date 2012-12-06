/*
 * File:   MainWindowController.cpp
 * Author: void
 *
 * Created on September 22, 2012, 9:43 PM
 */

#include "MainWindowController.h"

#include "IMainWindow.h"
#include "IRegularView.h"

#include "GuiManager.h"
#include "AboutWindowController.h"
#include "MappingToolWindowController.h"

MainWindowController::MainWindowController(IMainWindowPtr view):
m_MainWindowView(view)
{
    m_View = static_cast<IRegularView*>(m_MainWindowView.get());

    AttachViewSlots();
}

MainWindowController::~MainWindowController()
{

}

void MainWindowController::AttachViewSlots()
{
    m_MainWindowView->AttachOn(IMainWindow::E_ON_ABOUT_CLICKED, std::bind(&MainWindowController::OnAboutClicked, this));
    m_MainWindowView->AttachOn(IMainWindow::E_ON_MAPPING_TOOL_CLICKED, std::bind(&MainWindowController::OnMappingClicked, this));
}

void MainWindowController::OnAboutClicked()
{
    AboutWindowControllerPtr about = GuiManager::getRef().ForParent(m_View).CreateAboutWindow();
    about->View().ShowView();
}

void MainWindowController::OnMappingClicked()
{
    MappingToolWindowControllerPtr mapping = GuiManager::getRef().ForParent(m_View).CreateMappingToolWindow();
    mapping->View().ShowView();
}

void MainWindowController::OnAtlasClicked()
{

}