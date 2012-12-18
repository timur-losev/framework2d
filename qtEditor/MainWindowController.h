/*
 * File:   MainWindowController.h
 * Author: void
 *
 * Created on September 22, 2012, 9:43 PM
 */

#ifndef MAINWINDOWCONTROLLER_H
#    define	MAINWINDOWCONTROLLER_H

#    include "IRegularController.h"
#include <QtCore/qnamespace.h>	// for Qt::MouseButton

SHARED_PTR_FORWARD(IMainWindow);
SHARED_PTR_FORWARD(LevelManager);
SHARED_PTR_FORWARD(EditablePagedLevel);
SHARED_PTR_FORWARD(EditFrameController);

class MainWindowController : public IRegularController
{
private:
    IMainWindowPtr          m_MainWindowView;
    EditFrameControllerPtr  m_EditFrameController;
    LevelManagerPtr         m_LevelManager;
    EditablePagedLevelPtr   m_Level;
public:

    MainWindowController(IMainWindowPtr view);
    ~MainWindowController();

    void SetEditFrame(EditFrameControllerPtr);

private:
    void AttachViewSlots();

    void OnAboutClicked();
    void OnMappingClicked();
    void OnAtlasClicked();
    void OnViewShowed();

    void CreateNewLevel();

    void OnMouseMove(int x, int y, Qt::MouseButton button);
    void OnMouseDown(int x, int y, Qt::MouseButton button);
    void OnMouseUp(int x, int y, Qt::MouseButton button);
    void OnMouseWheel(int delta, int direction, int x, int y);
    void OnKeyboardEvent(irr::EKEY_CODE, EButtonState);


    //Signals from EditFrame
    void OnAddNewEmptyObject();
} ;

#endif	/* MAINWINDOWCONTROLLER_H */

