/********************************************************************************
** Form generated from reading UI file 'EditFrame.ui'
**
** Created: Tue 25. Dec 22:49:34 2012
**      by: Qt User Interface Compiler version 4.8.3
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
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditFrame
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *toolButtonsWidget;
    QPushButton *addNewObjectButton;
    QToolBox *toolBox;
    QWidget *geometryPropertiesPage;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_4;
    QGridLayout *geometryPropertiesGridLayout;
    QWidget *page_2;

    void setupUi(QFrame *EditFrame)
    {
        if (EditFrame->objectName().isEmpty())
            EditFrame->setObjectName(QString::fromUtf8("EditFrame"));
        EditFrame->resize(1081, 602);
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

        toolBox = new QToolBox(EditFrame);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        geometryPropertiesPage = new QWidget();
        geometryPropertiesPage->setObjectName(QString::fromUtf8("geometryPropertiesPage"));
        geometryPropertiesPage->setGeometry(QRect(0, 0, 1061, 492));
        gridLayout = new QGridLayout(geometryPropertiesPage);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scrollArea = new QScrollArea(geometryPropertiesPage);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1041, 472));
        gridLayout_4 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        geometryPropertiesGridLayout = new QGridLayout();
        geometryPropertiesGridLayout->setSpacing(6);
        geometryPropertiesGridLayout->setObjectName(QString::fromUtf8("geometryPropertiesGridLayout"));

        gridLayout_4->addLayout(geometryPropertiesGridLayout, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);

        toolBox->addItem(geometryPropertiesPage, QString::fromUtf8("Geometry"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 1061, 492));
        toolBox->addItem(page_2, QString::fromUtf8("Page 2"));

        verticalLayout->addWidget(toolBox);


        retranslateUi(EditFrame);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditFrame);
    } // setupUi

    void retranslateUi(QFrame *EditFrame)
    {
        EditFrame->setWindowTitle(QApplication::translate("EditFrame", "Frame", 0, QApplication::UnicodeUTF8));
        addNewObjectButton->setText(QApplication::translate("EditFrame", "+", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(geometryPropertiesPage), QApplication::translate("EditFrame", "Geometry", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("EditFrame", "Page 2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditFrame: public Ui_EditFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITFRAME_H
