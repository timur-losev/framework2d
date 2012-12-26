/********************************************************************************
** Form generated from reading UI file 'EditFrame.ui'
**
** Created: Wed Dec 26 01:07:40 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITFRAME_H
#define UI_EDITFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditFrame
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *toolButtonsWidget;
    QPushButton *addNewObjectButton;
    QTableView *tableView;

    void setupUi(QFrame *EditFrame)
    {
        if (EditFrame->objectName().isEmpty())
            EditFrame->setObjectName(QString::fromUtf8("EditFrame"));
        EditFrame->resize(901, 339);
        EditFrame->setFrameShape(QFrame::Box);
        EditFrame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(EditFrame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        toolButtonsWidget = new QWidget(EditFrame);
        toolButtonsWidget->setObjectName(QString::fromUtf8("toolButtonsWidget"));
        toolButtonsWidget->setMinimumSize(QSize(0, 30));
        addNewObjectButton = new QPushButton(toolButtonsWidget);
        addNewObjectButton->setObjectName(QString::fromUtf8("addNewObjectButton"));
        addNewObjectButton->setGeometry(QRect(0, 0, 31, 31));

        verticalLayout->addWidget(toolButtonsWidget);

        tableView = new QTableView(EditFrame);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);


        retranslateUi(EditFrame);

        QMetaObject::connectSlotsByName(EditFrame);
    } // setupUi

    void retranslateUi(QFrame *EditFrame)
    {
        EditFrame->setWindowTitle(QApplication::translate("EditFrame", "Frame", 0, QApplication::UnicodeUTF8));
        addNewObjectButton->setText(QApplication::translate("EditFrame", "+", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditFrame: public Ui_EditFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITFRAME_H
