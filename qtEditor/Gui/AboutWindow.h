/*
 * File:   AboutWindow.h
 * Author: void
 *
 * Created on September 23, 2012, 7:39 PM
 */

#ifndef _ABOUTWINDOW_H
#    define	_ABOUTWINDOW_H

#    include "ui_AboutWindow.hpp"
#    include "IAboutWindow.h"

class AboutWindow : public QDialog, public IAboutWindow
{
    Q_OBJECT

private:
    Ui::AboutWindow widget;
public:
    AboutWindow(QWidget* parent = nullptr);
    ~AboutWindow();

    virtual void ShowView();
    virtual void HideView();

    virtual const char* DebugName() const
    {
        return "AboutWindow";
    }
} ;

#endif	/* _ABOUTWINDOW_H */
