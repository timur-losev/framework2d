/*
 * File:   MainWindowController.h
 * Author: void
 *
 * Created on September 22, 2012, 9:43 PM
 */

#ifndef MAINWINDOWCONTROLLER_H
#    define	MAINWINDOWCONTROLLER_H

#    include "IRegularController.h"
#    include "SharedPointer.h"

SHARED_PTR_FORWARD(IMainWindow);

class MainWindowController : public IRegularController
{
private:
    IMainWindowPtr m_MainWindowView;
public:

    MainWindowController(IMainWindowPtr view);
    ~MainWindowController();

private:
    void AttachViewSlots();

    void OnAboutClicked();
    void OnMappingClicked();
    void OnAtlasClicked();

} ;

#endif	/* MAINWINDOWCONTROLLER_H */

