/*
 * File:   GuiManager.h
 * Author: void
 *
 * Created on September 23, 2012, 12:00 PM
 */

#ifndef GUIMANAGER_H
#    define	GUIMANAGER_H

#    include <Singleton.h>
#    include "IRegularView.h"

SHARED_PTR_FORWARD(MainWindowController);
SHARED_PTR_FORWARD(AboutWindowController);
SHARED_PTR_FORWARD(MappingToolWindowController);
SHARED_PTR_FORWARD(EditFrameController);

class GuiManager : public Common::Singleton<GuiManager>
{
private:

    AboutWindowControllerPtr            m_AboutWindow;
    MainWindowControllerPtr             m_MainWindow;
    MappingToolWindowControllerPtr      m_MappingToolWindow;
    EditFrameControllerPtr              m_EditFrame;

    IRegularView*                       m_ForParentView;
    bool_t                              m_Modality;

public:
    GuiManager();
    ~GuiManager();

    void                               CreateGui();
    void                               DestroyGui();

    GuiManager&                        ForParent(IRegularView*);
    GuiManager&                        WindowModality(bool_t value);

    MainWindowControllerPtr            CreateMainWindow();
    AboutWindowControllerPtr           CreateAboutWindow();
    MappingToolWindowControllerPtr     CreateMappingToolWindow();
    EditFrameControllerPtr             CreateEditFrame();
} ;

#endif	/* GUIMANAGER_H */

