/********************************************************************************
** Form generated from reading UI file 'MappingToolWindow.ui'
**
** Created: Wed 13. Mar 18:06:34 2013
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
    QTabWidget *tabWidget;
    QWidget *mapping;
    QWidget *verticalLayoutWidget;
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
    QWidget *menusWidget;

    void setupUi(QDialog *MappingToolWindow)
    {
        if (MappingToolWindow->objectName().isEmpty())
            MappingToolWindow->setObjectName(QString::fromUtf8("MappingToolWindow"));
        MappingToolWindow->resize(1024, 792);
        tabWidget = new QTabWidget(MappingToolWindow);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 40, 1001, 741));
        mapping = new QWidget();
        mapping->setObjectName(QString::fromUtf8("mapping"));
        verticalLayoutWidget = new QWidget(mapping);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 1001, 751));
        mainSizer = new QVBoxLayout(verticalLayoutWidget);
        mainSizer->setObjectName(QString::fromUtf8("mainSizer"));
        mainSizer->setSizeConstraint(QLayout::SetDefaultConstraint);
        mainSizer->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(verticalLayoutWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
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
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(3);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(renderFrame->sizePolicy().hasHeightForWidth());
        renderFrame->setSizePolicy(sizePolicy1);
        renderFrame->setMinimumSize(QSize(200, 200));
        renderFrame->setFrameShape(QFrame::StyledPanel);
        renderFrame->setFrameShadow(QFrame::Raised);
        splitter->addWidget(renderFrame);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
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

        toolWidget = new QWidget(verticalLayoutWidget);
        toolWidget->setObjectName(QString::fromUtf8("toolWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(toolWidget->sizePolicy().hasHeightForWidth());
        toolWidget->setSizePolicy(sizePolicy3);
        toolWidget->setMinimumSize(QSize(0, 25));
        toolWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        showAll = new QPushButton(toolWidget);
        showAll->setObjectName(QString::fromUtf8("showAll"));
        showAll->setGeometry(QRect(0, 0, 23, 23));
        showAll->setCheckable(true);

        mainSizer->addWidget(toolWidget);

        tabWidget->addTab(mapping, QString());
        animation = new QWidget();
        animation->setObjectName(QString::fromUtf8("animation"));
        tabWidget->addTab(animation, QString());
        menusWidget = new QWidget(MappingToolWindow);
        menusWidget->setObjectName(QString::fromUtf8("menusWidget"));
        menusWidget->setGeometry(QRect(10, 10, 999, 25));
        sizePolicy3.setHeightForWidth(menusWidget->sizePolicy().hasHeightForWidth());
        menusWidget->setSizePolicy(sizePolicy3);
        menusWidget->setMinimumSize(QSize(0, 25));

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
