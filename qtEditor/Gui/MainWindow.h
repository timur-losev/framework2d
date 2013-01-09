/*
 * File:   MainWindow.h
 * Author: void
 *
 * Created on September 22, 2012, 8:41 PM
 */

#ifndef _MAINWINDOW_H
#    define	_MAINWINDOW_H

#    include "IMainWindow.h"
#    include "ui_MainWindow.hpp"

#    include "SharedPointer.h"

SHARED_PTR_FORWARD(QIrrControl);
class EditFrame;

class MainWindow : public QMainWindow, public IMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow    widget;
    QIrrControlPtr    m_IrrControl;
    EditFrame*        m_EditFrame; //naked ptr is safe here
public:
    MainWindow();
    ~MainWindow();

    virtual void ShowView();
    virtual void HideView();

    virtual const char* DebugName() const;

    void resizeEvent( QResizeEvent* evt);

    virtual void SetEditFrame(IRegularView& view);

private:
    virtual IIrrControlPtr GetControl();

private Q_SLOTS:
    //signaling

    void OnAboutClicked();
    void OnMappingToolClicked();
    void OnAtlasToolClicked();
} ;

#endif	/* _MAINWINDOW_H */
