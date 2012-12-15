/********************************************************************************
** Form generated from reading UI file 'AboutWindow.ui'
**
** Created: Sat Dec 15 12:29:05 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTWINDOW_H
#define UI_ABOUTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AboutWindow
{
public:
    QPushButton *OkButton;
    QLabel *label;

    void setupUi(QDialog *AboutWindow)
    {
        if (AboutWindow->objectName().isEmpty())
            AboutWindow->setObjectName(QString::fromUtf8("AboutWindow"));
        AboutWindow->resize(395, 138);
        OkButton = new QPushButton(AboutWindow);
        OkButton->setObjectName(QString::fromUtf8("OkButton"));
        OkButton->setGeometry(QRect(280, 100, 98, 27));
        label = new QLabel(AboutWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 241, 31));

        retranslateUi(AboutWindow);
        QObject::connect(OkButton, SIGNAL(clicked()), AboutWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(AboutWindow);
    } // setupUi

    void retranslateUi(QDialog *AboutWindow)
    {
        AboutWindow->setWindowTitle(QApplication::translate("AboutWindow", "AboutWindow", 0, QApplication::UnicodeUTF8));
        OkButton->setText(QApplication::translate("AboutWindow", "Ok", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AboutWindow", "Version 0.5.3. Jeka & Timur Inc.", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AboutWindow: public Ui_AboutWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTWINDOW_H
