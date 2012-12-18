/********************************************************************************
** Form generated from reading UI file 'EditFrame.ui'
**
** Created: Wed 19. Dec 00:41:52 2012
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
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_EditFrame
{
public:

    void setupUi(QFrame *EditFrame)
    {
        if (EditFrame->objectName().isEmpty())
            EditFrame->setObjectName(QString::fromUtf8("EditFrame"));
        EditFrame->resize(973, 339);
        EditFrame->setFrameShape(QFrame::Box);
        EditFrame->setFrameShadow(QFrame::Raised);

        retranslateUi(EditFrame);

        QMetaObject::connectSlotsByName(EditFrame);
    } // setupUi

    void retranslateUi(QFrame *EditFrame)
    {
        EditFrame->setWindowTitle(QApplication::translate("EditFrame", "Frame", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditFrame: public Ui_EditFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITFRAME_H
