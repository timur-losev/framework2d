/*
 * File:   MainWindow.h
 * Author: void
 *
 * Created on September 22, 2012, 8:41 PM
 */

#ifndef _MAINWINDOW_H
#    define	_MAINWINDOW_H

#    include "EdPrec.h"
#    include "IMainWindow.h"

#    include "ui_MainWindow.hpp"

#    include "SharedPointer.h"

SHARED_PTR_FORWARD(QIrrControl);

class MainWindow : public QMainWindow, public IMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow    widget;
    QIrrControlPtr    m_IrrControl;

public:
    MainWindow();
    ~MainWindow();

    virtual void ShowView();
    virtual void HideView();

    virtual const char* DebugName() const
    {
        return "MainWindow";
    }

private slots:
    //signaling

    void OnAboutClicked();
    void OnMappingToolClicked();
    void OnAtlasToolClicked();

	void resizeEvent( QResizeEvent* evt);
} ;

#endif	/* _MAINWINDOW_H */
