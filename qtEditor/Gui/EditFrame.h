#pragma once

#include "ui_EditFrame.hpp"
#include "IEditFrame.h"

#include <QtGui/QMenuBar>

class EditFrame: public QFrame, public IEditFrame
{
    Q_OBJECT
private:
    Ui::EditFrame   widget;
    QMenu*          m_AddNew_Menu;
protected:
public:

    EditFrame(QWidget* parent = nullptr);

    virtual void ShowView();
    virtual void HideView();
    virtual const char* DebugName() const;

    private Q_SLOTS:
        void OnAddEmptyObject();

};