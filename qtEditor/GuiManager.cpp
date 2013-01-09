/*
 * File:   GuiManager.cpp
 * Author: void
 *
 * Created on September 23, 2012, 12:00 PM
 */

#include "EdPrec.h"

#include "GuiManager.h"

SHARED_PTR_FORWARD(MainWindow);
SHARED_PTR_FORWARD(AboutWindow);
SHARED_PTR_FORWARD(MappingToolWindow);
SHARED_PTR_FORWARD(EditFrame);

#include "MainWindowController.h"
#include "IMainWindow.h"
#include "Gui/MainWindow.h"

#include "AboutWindowController.h"
#include "IAboutWindow.h"
#include "Gui/AboutWindow.h"

#include "MappingToolWindowController.h"
#include "IMappingToolWindow.h"
#include "Gui/MappingToolWindow.h"

#include "EditFrameController.h"
#include "IEditFrame.h"
#include "Gui/EditFrame.h"

#include <QtCore/qnamespace.h>
#include <QtGui/QWidget>

SINGLETON_SETUP(GuiManager);

////////////////////////////////////////////////////////////////////////////////
#define LOOK_UP_PARENT\
    QWidget* parent = nullptr;\
    if (m_ForParentView)\
    {\
        parent = dynamic_cast<QWidget*>(m_ForParentView);\
        APP_API_ASSERT("RTTI error while looking up the parent" && parent);\
        m_ForParentView = nullptr;\
    }\

#define APPLY_MODALITY_FOR(__viewname)\
if (m_Modality){\
__viewname->setWindowModality(Qt::WindowModal);\
m_Modality = FALSE;}\

////////////////////////////////////////////////////////////////////////////////


GuiManager::GuiManager():
m_ForParentView(nullptr),
m_Modality(false)
{
    SINGLETON_ENABLE_THIS;
}

GuiManager::~GuiManager()
{
}

void GuiManager::CreateGui()
{
}

void GuiManager::DestroyGui()
{
}

MainWindowControllerPtr GuiManager::CreateMainWindow()
{
    MainWindowPtr view(new MainWindow());
    m_MainWindow.reset(new MainWindowController(view));

    return m_MainWindow;
}

AboutWindowControllerPtr GuiManager::CreateAboutWindow()
{
    LOOK_UP_PARENT

    AboutWindowPtr view(new AboutWindow(parent));
    m_AboutWindow.reset(new AboutWindowController(view));

    APPLY_MODALITY_FOR(view);
    return m_AboutWindow;
}

MappingToolWindowControllerPtr GuiManager::CreateMappingToolWindow()
{
    LOOK_UP_PARENT

    MappingToolWindowPtr view(new MappingToolWindow(parent));
    m_MappingToolWindow.reset(new MappingToolWindowController(view));

    APPLY_MODALITY_FOR(view);

    return m_MappingToolWindow;
}

EditFrameControllerPtr GuiManager::CreateEditFrame()
{
    LOOK_UP_PARENT

    EditFramePtr view(new EditFrame(parent));
    m_EditFrame.reset(new EditFrameController(view));

    APPLY_MODALITY_FOR(view);

    return m_EditFrame;
}

GuiManager& GuiManager::ForParent(IRegularView* parent)
{
    m_ForParentView = parent;

    return *this;
}

GuiManager& GuiManager::WindowModality(bool_t value)
{
    m_Modality = value;

    return *this;
}