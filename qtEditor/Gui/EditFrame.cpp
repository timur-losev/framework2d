#include "EdPrec.h"
#include "EditFrame.h"

EditFrame::EditFrame(QWidget* parent): QFrame(parent)
{
    widget.setupUi(this);
    
    m_AddNew_Menu = new QMenu(widget.toolButtonsWidget);
    widget.addNewObjectButton->setMenu(m_AddNew_Menu);

    QAction* actionAddEmptyObject = new QAction(this);
    actionAddEmptyObject->setObjectName(QString::fromUtf8("actionAddEmptyObject"));
    m_AddNew_Menu->addAction(actionAddEmptyObject);
    actionAddEmptyObject->setText(QApplication::translate("EditFrame", "Add empty object", 0, QApplication::UnicodeUTF8));
    connect(actionAddEmptyObject, SIGNAL(activated()), this, SLOT(OnAddEmptyObject()));
    //setStyleSheet("* { background-color:rgb(125,100,50);color:rgb(200,150,100); padding: 7px}}");
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

