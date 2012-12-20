/*
 * File:   MappingToolWindow.h
 * Author: void
 *
 * Created on September 24, 2012, 12:09 AM
 */

#ifndef _MAPPINGTOOLWINDOW_H
#    define	_MAPPINGTOOLWINDOW_H

#    include "ui_MappingToolWindow.hpp"
#    include "IMappingToolWindow.h"
#    include <QtGui/QMenuBar>

SHARED_PTR_FORWARD(QIrrControl);

class MappingToolWindow :
        public QDialog,
        public IMappingToolWindow
#ifdef USE_INVOKER
        ,public Common::Invoker
#endif
{
    Q_OBJECT
private:
    Ui::MappingToolWindow widget;

    QMenuBar*   m_MenuBar;
    QMenu*      m_FileMenu, *m_ToolsMenu;

    QIrrControlPtr    m_IrrControl;
protected:
    //void resizeEvent(QResizeEvent *);
public:
    MappingToolWindow(QWidget* parent = nullptr);
    ~MappingToolWindow();

    virtual void ShowView();
    virtual void HideView();

    virtual const char* DebugName() const;

    virtual IIrrControlPtr GetControl();

    virtual void RefreshSpriteInfo(SpriteTexturesListConstPtr textures, SpriteFramesListConstPtr frames);

private Q_SLOTS:
    void OnOpenFileSelected();
    void OnSaveFile();
    void OnOpenTextureSelected();
	void OnFrameSelected(QModelIndex index);

    void closeEvent (QCloseEvent * ev);
    void resizeEvent(QResizeEvent *evt);
    void DelayedUpdate();
} ;

#endif	/* _MAPPINGTOOLWINDOW_H */
