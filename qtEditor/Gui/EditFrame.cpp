#include "EdPrec.h"
#include "EditFrame.h"

EditFrame::EditFrame(QWidget* parent): QFrame(parent)
{
    widget.setupUi(this);

    m_MenuBar = new QMenuBar(this);
    m_MenuBar->setObjectName(QString::fromUtf8("MenuBar"));
    m_MenuBar->setGeometry(0, 0, 300, 20);
    m_AddNewMenu = new QMenu(m_MenuBar);
    m_AddNewMenu->setObjectName(QString::fromUtf8("FileMenu"));

    m_AddNewMenu->setTitle(QApplication::translate("EditFrame", "+", 0, QApplication::UnicodeUTF8));

    m_MenuBar->addAction(m_AddNewMenu->menuAction());

    QAction* actionAddEmptyObject = new QAction(this);
    actionAddEmptyObject->setObjectName(QString::fromUtf8("actionAddEmptyObject"));



    m_AddNewMenu->addAction(actionAddEmptyObject);


    actionAddEmptyObject->setText(QApplication::translate("EditFrame", "Add empty object", 0, QApplication::UnicodeUTF8));

    connect(actionAddEmptyObject, SIGNAL(activated()), this, SLOT(OnAddEmptyObject()));
}

void EditFrame::ShowView()
{
    show();

    CallBack(EB_ON_SHOW);
}

void EditFrame::HideView()
{
    hide();

    CallBack(EB_ON_CLOSE);
}

const char* EditFrame::DebugName() const
{
    return "EditFrame";
}

void EditFrame::OnAddEmptyObject()
{
    CallBack(ES_ON_ADD_EMPTY_OBJECT);
}

