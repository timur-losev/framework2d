/********************************************************************************
** Form generated from reading UI file 'MappingToolWindow.ui'
**
** Created: Mon 3. Jun 17:40:08 2013
**      by: Qt User Interface Compiler version 4.8.1
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
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSplitter>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MappingToolWindow
{
public:
    QGridLayout *gridLayout;
    QWidget *menusWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *mapping;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *mainSizer;
    QSplitter *splitter;
    QFrame *renderFrame;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_9;
    QVBoxLayout *verticalLayout_1;
    QLabel *label_11;
    QTableView *mapTableView;
    QLineEdit *fastEdit;
    QLabel *label_12;
    QListView *texturesListWidget;
    QPushButton *addTextureButton;
    QPushButton *removeTextureButton;
    QWidget *toolWidget;
    QPushButton *showAll;
    QWidget *animation;

    void setupUi(QDialog *MappingToolWindow)
    {
        if (MappingToolWindow->objectName().isEmpty())
            MappingToolWindow->setObjectName(QString::fromUtf8("MappingToolWindow"));
        MappingToolWindow->resize(1087, 866);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(MappingToolWindow->sizePolicy().hasHeightForWidth());
        MappingToolWindow->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(MappingToolWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        menusWidget = new QWidget(MappingToolWindow);
        menusWidget->setObjectName(QString::fromUtf8("menusWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(menusWidget->sizePolicy().hasHeightForWidth());
        menusWidget->setSizePolicy(sizePolicy1);
        menusWidget->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(menusWidget, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        tabWidget = new QTabWidget(MappingToolWindow);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        mapping = new QWidget();
        mapping->setObjectName(QString::fromUtf8("mapping"));
        sizePolicy.setHeightForWidth(mapping->sizePolicy().hasHeightForWidth());
        mapping->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(mapping);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        mainSizer = new QVBoxLayout();
        mainSizer->setObjectName(QString::fromUtf8("mainSizer"));
        mainSizer->setSizeConstraint(QLayout::SetMaximumSize);
        splitter = new QSplitter(mapping);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy2);
        splitter->setFrameShape(QFrame::NoFrame);
        splitter->setFrameShadow(QFrame::Plain);
        splitter->setLineWidth(1);
        splitter->setMidLineWidth(0);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(false);
        splitter->setHandleWidth(4);
        splitter->setChildrenCollapsible(false);
        renderFrame = new QFrame(splitter);
        renderFrame->setObjectName(QString::fromUtf8("renderFrame"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(3);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(renderFrame->sizePolicy().hasHeightForWidth());
        renderFrame->setSizePolicy(sizePolicy3);
        renderFrame->setMinimumSize(QSize(200, 200));
        renderFrame->setFrameShape(QFrame::StyledPanel);
        renderFrame->setFrameShadow(QFrame::Raised);
        splitter->addWidget(renderFrame);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy4);
        groupBox->setMinimumSize(QSize(200, 0));
        groupBox->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_9 = new QGridLayout(groupBox);
        gridLayout_9->setSpacing(0);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setContentsMargins(5, 0, 5, 5);
        verticalLayout_1 = new QVBoxLayout();
        verticalLayout_1->setSpacing(0);
        verticalLayout_1->setObjectName(QString::fromUtf8("verticalLayout_1"));
        verticalLayout_1->setContentsMargins(0, -1, -1, -1);
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setIndent(7);

        verticalLayout_1->addWidget(label_11);

        mapTableView = new QTableView(groupBox);
        mapTableView->setObjectName(QString::fromUtf8("mapTableView"));
        mapTableView->setContextMenuPolicy(Qt::CustomContextMenu);
        mapTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        mapTableView->horizontalHeader()->setDefaultSectionSize(50);
        mapTableView->horizontalHeader()->setMinimumSectionSize(23);
        mapTableView->verticalHeader()->setDefaultSectionSize(23);
        mapTableView->verticalHeader()->setMinimumSectionSize(15);

        verticalLayout_1->addWidget(mapTableView);

        fastEdit = new QLineEdit(groupBox);
        fastEdit->setObjectName(QString::fromUtf8("fastEdit"));
        fastEdit->setMaxLength(1024);

        verticalLayout_1->addWidget(fastEdit);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMargin(0);
        label_12->setIndent(7);

        verticalLayout_1->addWidget(label_12);

        texturesListWidget = new QListView(groupBox);
        texturesListWidget->setObjectName(QString::fromUtf8("texturesListWidget"));
        texturesListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_1->addWidget(texturesListWidget);

        addTextureButton = new QPushButton(groupBox);
        addTextureButton->setObjectName(QString::fromUtf8("addTextureButton"));

        verticalLayout_1->addWidget(addTextureButton);

        removeTextureButton = new QPushButton(groupBox);
        removeTextureButton->setObjectName(QString::fromUtf8("removeTextureButton"));

        verticalLayout_1->addWidget(removeTextureButton);


        gridLayout_9->addLayout(verticalLayout_1, 0, 0, 1, 1);

        splitter->addWidget(groupBox);

        mainSizer->addWidget(splitter);

        toolWidget = new QWidget(mapping);
        toolWidget->setObjectName(QString::fromUtf8("toolWidget"));
        sizePolicy1.setHeightForWidth(toolWidget->sizePolicy().hasHeightForWidth());
        toolWidget->setSizePolicy(sizePolicy1);
        toolWidget->setMinimumSize(QSize(0, 25));
        toolWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        showAll = new QPushButton(toolWidget);
        showAll->setObjectName(QString::fromUtf8("showAll"));
        showAll->setGeometry(QRect(0, 0, 23, 23));
        showAll->setCheckable(true);

        mainSizer->addWidget(toolWidget);


        verticalLayout_3->addLayout(mainSizer);

        tabWidget->addTab(mapping, QString());
        animation = new QWidget();
        animation->setObjectName(QString::fromUtf8("animation"));
        QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy5.setHorizontalStretch(1);
        sizePolicy5.setVerticalStretch(1);
        sizePolicy5.setHeightForWidth(animation->sizePolicy().hasHeightForWidth());
        animation->setSizePolicy(sizePolicy5);
        tabWidget->addTab(animation, QString());

        verticalLayout->addWidget(tabWidget);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);


        retranslateUi(MappingToolWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MappingToolWindow);
    } // setupUi

    void retranslateUi(QDialog *MappingToolWindow)
    {
        MappingToolWindow->setWindowTitle(QApplication::translate("MappingToolWindow", "MappingToolWindow", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MappingToolWindow", "Map box", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MappingToolWindow", "Map list", 0, QApplication::UnicodeUTF8));
        fastEdit->setPlaceholderText(QApplication::translate("MappingToolWindow", "Fast properties editor", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MappingToolWindow", "Textures list", 0, QApplication::UnicodeUTF8));
        addTextureButton->setText(QApplication::translate("MappingToolWindow", "Add Texture", 0, QApplication::UnicodeUTF8));
        removeTextureButton->setText(QApplication::translate("MappingToolWindow", "Remove Texture", 0, QApplication::UnicodeUTF8));
        showAll->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(mapping), QApplication::translate("MappingToolWindow", "Mapping Tool", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(animation), QApplication::translate("MappingToolWindow", "Animation Tool", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MappingToolWindow: public Ui_MappingToolWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPPINGTOOLWINDOW_H
