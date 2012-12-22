/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Sat 22. Dec 19:31:42 2012
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionAtlas;
    QAction *actionMapping;
    QAction *actionLibrary;
    QAction *actionToolbox;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGridLayout *mainSizer;
    QFrame *renderFrame;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuAbout;
    QMenu *menuWindows;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(999, 913);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAtlas = new QAction(MainWindow);
        actionAtlas->setObjectName(QString::fromUtf8("actionAtlas"));
        actionMapping = new QAction(MainWindow);
        actionMapping->setObjectName(QString::fromUtf8("actionMapping"));
        actionLibrary = new QAction(MainWindow);
        actionLibrary->setObjectName(QString::fromUtf8("actionLibrary"));
        actionToolbox = new QAction(MainWindow);
        actionToolbox->setObjectName(QString::fromUtf8("actionToolbox"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mainSizer = new QGridLayout();
        mainSizer->setObjectName(QString::fromUtf8("mainSizer"));
        mainSizer->setVerticalSpacing(14);
        mainSizer->setContentsMargins(0, -1, -1, -1);
        renderFrame = new QFrame(centralwidget);
        renderFrame->setObjectName(QString::fromUtf8("renderFrame"));
        renderFrame->setMinimumSize(QSize(800, 600));
        renderFrame->setFrameShape(QFrame::Box);
        renderFrame->setFrameShadow(QFrame::Raised);

        mainSizer->addWidget(renderFrame, 0, 0, 1, 1);


        gridLayout->addLayout(mainSizer, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 999, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuTools = new QMenu(menubar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        menuWindows = new QMenu(menubar);
        menuWindows->setObjectName(QString::fromUtf8("menuWindows"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuTools->menuAction());
        menubar->addAction(menuWindows->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuTools->addAction(actionAtlas);
        menuTools->addAction(actionMapping);
        menuAbout->addAction(actionAbout);
        menuWindows->addAction(actionLibrary);
        menuWindows->addAction(actionToolbox);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionAtlas->setText(QApplication::translate("MainWindow", "Atlas", 0, QApplication::UnicodeUTF8));
        actionMapping->setText(QApplication::translate("MainWindow", "Mapping", 0, QApplication::UnicodeUTF8));
        actionLibrary->setText(QApplication::translate("MainWindow", "Library", 0, QApplication::UnicodeUTF8));
        actionToolbox->setText(QApplication::translate("MainWindow", "Toolbox", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("MainWindow", "?", 0, QApplication::UnicodeUTF8));
        menuWindows->setTitle(QApplication::translate("MainWindow", "Windows", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
