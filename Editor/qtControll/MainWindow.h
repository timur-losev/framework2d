/*
 * File:   MainWindow.h
 * Author: void
 *
 * Created on September 21, 2012, 11:26 PM
 */

#ifndef _MAINWINDOW_H
#    define	_MAINWINDOW_H

#    include "ui_MainWindow.hpp"

class QIrrControll;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private slots:
    void OnButton();

    QIrrControll* m_Controll;
protected:
    virtual bool event(QEvent* event);

private:
    Ui::MainWindow widget;

} ;

#endif	/* _MAINWINDOW_H */
