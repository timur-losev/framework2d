/*
 * File:   MainWindowController.cpp
 * Author: void
 *
 * Created on September 22, 2012, 9:43 PM
 */
#include "EdPrec.h"
#include "MainWindowController.h"

#include "IMainWindow.h"
#include "IRegularView.h"
#include "IEditFrame.h"

#include "GuiManager.h"
#include "AboutWindowController.h"
#include "MappingToolWindowController.h"
#include "EditFrameController.h"

#include "LevelManager.h"
#include "EditablePagedLevel.h"
#include "IIrrControl.h"

MainWindowController::MainWindowController(IMainWindowPtr view):
m_MainWindowView(view)
{
    m_View = CAST_TO_REGULAR_VIEW(m_MainWindowView.get());

    AttachViewSlots();
}

MainWindowController::~MainWindowController()
{

}

void MainWindowController::AttachViewSlots()
{
    m_MainWindowView->AttachOn(IMainWindow::E_ON_ABOUT_CLICKED, std::bind(&MainWindowController::OnAboutClicked, this));
    m_MainWindowView->AttachOn(IMainWindow::E_ON_MAPPING_TOOL_CLICKED, std::bind(&MainWindowController::OnMappingClicked, this));

    m_View->AttachOn(IMainWindow::EB_ON_SHOW, std::bind(&MainWindowController::OnViewShowed, this));
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

void MainWindowController::OnViewShowed()
{
    CreateNewLevel();
}

void MainWindowController::CreateNewLevel()
{
    IIrrControlPtr control = m_MainWindowView->GetControl();

    m_LevelManager.reset(new LevelManager());
    m_Level.reset(new EditablePagedLevel("TestLevel"));
    ThreadPtr thr = control->Thread();
    m_Level->CreateInvoker(thr);
    m_Level->Init();
    m_LevelManager->AttachLevel(m_Level);
    control->PushLevelManager(m_LevelManager);

    control->AttachOnMouseEventSignal(boost::bind(&MainWindowController::OnMouseMove, this, _1, _2, _3));
    control->AttachOnMousePressEventSignal(boost::bind(&MainWindowController::OnMouseDown, this, _1, _2, _3));
    control->AttachOnMouseReleaseEventSignal(boost::bind(&MainWindowController::OnMouseUp, this, _1, _2, _3));
    control->AttachOnMouseWheelEventSignal(boost::bind(&MainWindowController::OnMouseWheel, this, _1, _2, _3, _4));
    control->AttachOnKeyboardEventSignal(boost::bind(&MainWindowController::OnKeyboardEvent, this, _1, _2));
}

void MainWindowController::OnMouseMove( int x, int y, Qt::MouseButton button )
{
    if (m_Level)
    {
        m_Level->OnMouseMove(x, y);
    }
}

void MainWindowController::OnMouseDown( int x, int y, Qt::MouseButton button )
{
    if (m_Level)
    {
        EMouseButtons btn = EMB_NONE;
        if (Qt::LeftButton == button)
        {
            btn = EMB_LEFT;
        }
        else if (Qt::RightButton == button)
        {
            btn = EMB_RIGHT;
        }
        else if (Qt::MiddleButton == button)
        {
            btn = EMB_MIDDLE;
        }

        m_Level->OnMouseDown(btn, x, y);
    }
}

void MainWindowController::OnMouseUp( int x, int y, Qt::MouseButton button )
{
    if (m_Level)
    {
        EMouseButtons btn = EMB_NONE;
        if (Qt::LeftButton == button)
        {
            btn = EMB_LEFT;
        }
        else if (Qt::RightButton == button)
        {
            btn = EMB_RIGHT;
        }
        else if (Qt::MiddleButton == button)
        {
            btn = EMB_MIDDLE;
        }

        m_Level->OnMouseUp(btn, x, y);
    }
}

void MainWindowController::OnMouseWheel( int delta, int direction, int x, int y )
{
    
}

void MainWindowController::OnKeyboardEvent( irr::EKEY_CODE c, EButtonState s)
{
    if (m_Level)
    {
        if (s == EBS_KEY_DOWN)
        {
            m_Level->OnKeyDown(c);
        }
        else if (s == EBS_KEY_UP)
        {
            //TODO
        }
    }
}

void MainWindowController::SetEditFrame( EditFrameControllerPtr frame)
{
    m_MainWindowView->SetEditFrame(frame->View());

    m_EditFrameController = frame;
    //subscribe on Edit signals
    IEditFramePtr frameView = frame->GetFrameView();

    frameView->AttachOn(IEditFrame::ES_ON_ADD_EMPTY_OBJECT, std::bind(&MainWindowController::OnAddNewEmptyObject, this));
}

void MainWindowController::OnAddNewEmptyObject()
{

}
