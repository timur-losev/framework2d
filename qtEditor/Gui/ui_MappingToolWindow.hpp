/********************************************************************************
** Form generated from reading UI file 'MappingToolWindow.ui'
**
** Created: Sat 15. Dec 23:22:16 2012
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPPINGTOOLWINDOW_H
#define UI_MAPPINGTOOLWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MappingToolWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *mainSizer;
    QFrame *renderFrame;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableView *mapTableView;
    QPushButton *addFramesButton;
    QPushButton *removeFrameButton;
    QLabel *label_2;
    QListView *texturesListWidget;
    QPushButton *addTextureButton;
    QPushButton *removeTextureButton;
    QWidget *toolWidget;
    QPushButton *showAll;
    QWidget *menusWidget;

    void setupUi(QDialog *MappingToolWindow)
    {
        if (MappingToolWindow->objectName().isEmpty())
            MappingToolWindow->setObjectName(QString::fromUtf8("MappingToolWindow"));
        MappingToolWindow->resize(1021, 857);
        horizontalLayout = new QHBoxLayout(MappingToolWindow);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        mainSizer = new QGridLayout();
        mainSizer->setObjectName(QString::fromUtf8("mainSizer"));
        mainSizer->setVerticalSpacing(4);
        renderFrame = new QFrame(MappingToolWindow);
        renderFrame->setObjectName(QString::fromUtf8("renderFrame"));
        renderFrame->setFrameShape(QFrame::StyledPanel);
        renderFrame->setFrameShadow(QFrame::Raised);

        mainSizer->addWidget(renderFrame, 1, 0, 1, 1);

        groupBox = new QGroupBox(MappingToolWindow);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(200, 0));
        groupBox->setMaximumSize(QSize(120, 16777215));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(5, 0, 5, 5);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setIndent(7);

        verticalLayout->addWidget(label);

        mapTableView = new QTableView(groupBox);
        mapTableView->setObjectName(QString::fromUtf8("mapTableView"));
        mapTableView->horizontalHeader()->setDefaultSectionSize(50);
        mapTableView->horizontalHeader()->setMinimumSectionSize(23);
        mapTableView->verticalHeader()->setDefaultSectionSize(23);
        mapTableView->verticalHeader()->setMinimumSectionSize(15);

        verticalLayout->addWidget(mapTableView);

        addFramesButton = new QPushButton(groupBox);
        addFramesButton->setObjectName(QString::fromUtf8("addFramesButton"));

        verticalLayout->addWidget(addFramesButton);

        removeFrameButton = new QPushButton(groupBox);
        removeFrameButton->setObjectName(QString::fromUtf8("removeFrameButton"));

        verticalLayout->addWidget(removeFrameButton);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMargin(0);
        label_2->setIndent(7);

        verticalLayout->addWidget(label_2);

        texturesListWidget = new QListView(groupBox);
        texturesListWidget->setObjectName(QString::fromUtf8("texturesListWidget"));
        texturesListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(texturesListWidget);

        addTextureButton = new QPushButton(groupBox);
        addTextureButton->setObjectName(QString::fromUtf8("addTextureButton"));

        verticalLayout->addWidget(addTextureButton);

        removeTextureButton = new QPushButton(groupBox);
        removeTextureButton->setObjectName(QString::fromUtf8("removeTextureButton"));

        verticalLayout->addWidget(removeTextureButton);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);


        mainSizer->addWidget(groupBox, 1, 1, 1, 1);

        toolWidget = new QWidget(MappingToolWindow);
        toolWidget->setObjectName(QString::fromUtf8("toolWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolWidget->sizePolicy().hasHeightForWidth());
        toolWidget->setSizePolicy(sizePolicy);
        toolWidget->setMinimumSize(QSize(0, 25));
        toolWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        showAll = new QPushButton(toolWidget);
        showAll->setObjectName(QString::fromUtf8("showAll"));
        showAll->setGeometry(QRect(0, 0, 23, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/16x16/show_all.png"), QSize(), QIcon::Normal, QIcon::Off);
        showAll->setIcon(icon);

        mainSizer->addWidget(toolWidget, 2, 0, 1, 1);

        menusWidget = new QWidget(MappingToolWindow);
        menusWidget->setObjectName(QString::fromUtf8("menusWidget"));
        menusWidget->setMinimumSize(QSize(0, 25));

        mainSizer->addWidget(menusWidget, 0, 0, 1, 1);


        horizontalLayout->addLayout(mainSizer);


        retranslateUi(MappingToolWindow);

        QMetaObject::connectSlotsByName(MappingToolWindow);
    } // setupUi

    void retranslateUi(QDialog *MappingToolWindow)
    {
        MappingToolWindow->setWindowTitle(QApplication::translate("MappingToolWindow", "MappingToolWindow", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MappingToolWindow", "Map box", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MappingToolWindow", "Map list", 0, QApplication::UnicodeUTF8));
        addFramesButton->setText(QApplication::translate("MappingToolWindow", "Add frames", 0, QApplication::UnicodeUTF8));
        removeFrameButton->setText(QApplication::translate("MappingToolWindow", "Remove Frame", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MappingToolWindow", "Textures list", 0, QApplication::UnicodeUTF8));
        addTextureButton->setText(QApplication::translate("MappingToolWindow", "Add Texture", 0, QApplication::UnicodeUTF8));
        removeTextureButton->setText(QApplication::translate("MappingToolWindow", "Remove Texture", 0, QApplication::UnicodeUTF8));
        showAll->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MappingToolWindow: public Ui_MappingToolWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPPINGTOOLWINDOW_H
