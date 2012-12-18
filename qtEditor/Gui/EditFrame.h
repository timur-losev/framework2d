#pragma once

#include "ui_EditFrame.hpp"
#include "IEditFrame.h"

#include <QtGui/QMenuBar>

class EditFrame: public QFrame, public IEditFrame
{
    Q_OBJECT
private:
    Ui::EditFrame   widget;
    QMenuBar*       m_MenuBar;
    QMenu*          m_AddNewMenu;
protected:
public:

    EditFrame(QWidget* parent = nullptr);

    virtual void ShowView();
    virtual void HideView();
    virtual const char* DebugName() const;

    private Q_SLOTS:
        void OnAddEmptyObject();

};