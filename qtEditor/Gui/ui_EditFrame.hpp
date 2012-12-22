/********************************************************************************
** Form generated from reading UI file 'EditFrame.ui'
**
** Created: Sat 22. Dec 19:31:42 2012
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
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditFrame
{
public:
    QGridLayout *gridLayout_3;
    QToolBox *toolBox;
    QWidget *propertiesPage;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_14;
    QPushButton *pushButton_13;
    QPushButton *pushButton_10;
    QPushButton *pushButton_9;
    QPushButton *pushButton;
    QPushButton *pushButton_15;
    QPushButton *pushButton_11;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_12;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_2;
    QPushButton *pushButton_8;
    QPushButton *pushButton_16;
    QPushButton *pushButton_17;
    QPushButton *pushButton_18;
    QWidget *page_2;

    void setupUi(QFrame *EditFrame)
    {
        if (EditFrame->objectName().isEmpty())
            EditFrame->setObjectName(QString::fromUtf8("EditFrame"));
        EditFrame->resize(1081, 602);
        EditFrame->setFrameShape(QFrame::Box);
        EditFrame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(EditFrame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetNoConstraint);
        toolBox = new QToolBox(EditFrame);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        propertiesPage = new QWidget();
        propertiesPage->setObjectName(QString::fromUtf8("propertiesPage"));
        propertiesPage->setGeometry(QRect(0, 0, 1061, 528));
        gridLayout = new QGridLayout(propertiesPage);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scrollArea = new QScrollArea(propertiesPage);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1041, 508));
        gridLayout_4 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton_14 = new QPushButton(scrollAreaWidgetContents);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));

        gridLayout_2->addWidget(pushButton_14, 8, 1, 1, 1);

        pushButton_13 = new QPushButton(scrollAreaWidgetContents);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));

        gridLayout_2->addWidget(pushButton_13, 7, 1, 1, 1);

        pushButton_10 = new QPushButton(scrollAreaWidgetContents);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));

        gridLayout_2->addWidget(pushButton_10, 4, 1, 1, 1);

        pushButton_9 = new QPushButton(scrollAreaWidgetContents);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));

        gridLayout_2->addWidget(pushButton_9, 3, 1, 1, 1);

        pushButton = new QPushButton(scrollAreaWidgetContents);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_2->addWidget(pushButton, 2, 0, 1, 1);

        pushButton_15 = new QPushButton(scrollAreaWidgetContents);
        pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));

        gridLayout_2->addWidget(pushButton_15, 9, 1, 1, 1);

        pushButton_11 = new QPushButton(scrollAreaWidgetContents);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));

        gridLayout_2->addWidget(pushButton_11, 5, 1, 1, 1);

        pushButton_3 = new QPushButton(scrollAreaWidgetContents);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout_2->addWidget(pushButton_3, 4, 0, 1, 1);

        pushButton_4 = new QPushButton(scrollAreaWidgetContents);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout_2->addWidget(pushButton_4, 3, 0, 1, 1);

        pushButton_12 = new QPushButton(scrollAreaWidgetContents);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));

        gridLayout_2->addWidget(pushButton_12, 6, 1, 1, 1);

        pushButton_5 = new QPushButton(scrollAreaWidgetContents);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        gridLayout_2->addWidget(pushButton_5, 1, 0, 1, 1);

        pushButton_6 = new QPushButton(scrollAreaWidgetContents);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        gridLayout_2->addWidget(pushButton_6, 0, 0, 1, 1);

        pushButton_7 = new QPushButton(scrollAreaWidgetContents);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        gridLayout_2->addWidget(pushButton_7, 0, 1, 1, 1);

        pushButton_2 = new QPushButton(scrollAreaWidgetContents);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 2, 1, 1, 1);

        pushButton_8 = new QPushButton(scrollAreaWidgetContents);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));

        gridLayout_2->addWidget(pushButton_8, 1, 1, 1, 1);

        pushButton_16 = new QPushButton(scrollAreaWidgetContents);
        pushButton_16->setObjectName(QString::fromUtf8("pushButton_16"));

        gridLayout_2->addWidget(pushButton_16, 10, 1, 1, 1);

        pushButton_17 = new QPushButton(scrollAreaWidgetContents);
        pushButton_17->setObjectName(QString::fromUtf8("pushButton_17"));

        gridLayout_2->addWidget(pushButton_17, 11, 1, 1, 1);

        pushButton_18 = new QPushButton(scrollAreaWidgetContents);
        pushButton_18->setObjectName(QString::fromUtf8("pushButton_18"));

        gridLayout_2->addWidget(pushButton_18, 12, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);

        toolBox->addItem(propertiesPage, QString::fromUtf8("Properties"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 1061, 528));
        toolBox->addItem(page_2, QString::fromUtf8("Page 2"));

        gridLayout_3->addWidget(toolBox, 0, 0, 1, 1);


        retranslateUi(EditFrame);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditFrame);
    } // setupUi

    void retranslateUi(QFrame *EditFrame)
    {
        EditFrame->setWindowTitle(QApplication::translate("EditFrame", "Frame", 0, QApplication::UnicodeUTF8));
        pushButton_14->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_13->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_10->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_15->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_11->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_12->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_16->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_17->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_18->setText(QApplication::translate("EditFrame", "PushButton", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(propertiesPage), QApplication::translate("EditFrame", "Properties", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("EditFrame", "Page 2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditFrame: public Ui_EditFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITFRAME_H
