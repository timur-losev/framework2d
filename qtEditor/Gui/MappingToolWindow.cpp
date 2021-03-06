﻿/*
 * File:   MappingToolWindow.cpp
 * Author: void
 *
 * Created on September 24, 2012, 12:09 AM
 */
#include "EdPrec.h"
#include "MappingToolWindow.h"
#include <QtGui/QResizeEvent>
#include <QtGui/QFileDialog>

#include "QIrrControl.h"
#include <QtGui/QStandardItemModel>
#include <QtCore/QTimer>

MappingToolWindow::MappingToolWindow(QWidget* parent) : QDialog(parent, Qt::Window)
{
    widget.setupUi(this);

    m_MenuBar = new QMenuBar(widget.menusWidget);
    m_MenuBar->setObjectName(QString::fromUtf8("menuBar"));
    m_MenuBar->setGeometry(widget.menusWidget->geometry());

    m_FileMenu = new QMenu(m_MenuBar);
    m_FileMenu->setObjectName(QString::fromUtf8("fileMenu"));

    m_ToolsMenu = new QMenu(m_MenuBar);
    m_ToolsMenu ->setObjectName(QString::fromUtf8("toolsMenu"));

    QAction* actionOpenFile = new QAction(widget.menusWidget);
    actionOpenFile->setObjectName(QString::fromUtf8("actionOpenFile"));

    QAction* actionSaveFile = new QAction(widget.menusWidget);
    actionSaveFile->setObjectName(QString::fromUtf8("actionSaveFile"));

    QAction* actionClose = new QAction(widget.menusWidget);
    actionClose->setObjectName(QString::fromUtf8("actionClose"));

    QAction* actionOpenTexture = new QAction(widget.menusWidget);
    actionOpenTexture->setObjectName(QString::fromUtf8("actionOpenTexture"));

    m_MenuBar->addAction(m_FileMenu->menuAction());
    m_MenuBar->addAction(m_ToolsMenu->menuAction());

    m_FileMenu->addAction(actionOpenFile);
    m_FileMenu->addAction(actionSaveFile);
    m_FileMenu->addAction(actionOpenTexture);
    m_FileMenu->addSeparator();
    m_FileMenu->addAction(actionClose);

    m_FileMenu->setTitle(QApplication::translate("MappingToolWindow", "File", 0, QApplication::UnicodeUTF8));
    m_ToolsMenu->setTitle(QApplication::translate("MappingToolWindow", "Tools", 0, QApplication::UnicodeUTF8));

    actionClose->setText(QApplication::translate("MappingToolWindow", "Close", 0, QApplication::UnicodeUTF8));
    actionOpenFile->setText(QApplication::translate("MappingToolWindow", "Open", 0, QApplication::UnicodeUTF8));
    actionSaveFile->setText(QApplication::translate("MappingToolWindow", "Save", 0, QApplication::UnicodeUTF8));
    actionOpenTexture->setText(QApplication::translate("MappingToolWindow", "Open Texture", 0, QApplication::UnicodeUTF8));

	QIcon icon;
	std::string iconPath = std::string(MEDIA_PATH) + "Icons/16x16/show_all.png";
	icon.addFile(iconPath.c_str(), QSize(), QIcon::Normal, QIcon::Off);
    widget.showAll->setIcon(icon);

    connect(actionClose, SIGNAL(activated()), this, SLOT(close()));
    connect(actionOpenFile, SIGNAL(activated()), this, SLOT(OnOpenFileSelected()));
    connect(actionSaveFile, SIGNAL(activated()), this, SLOT(OnSaveFile()));
    connect(actionOpenTexture, SIGNAL(activated()), this, SLOT(OnOpenTextureSelected()));
	connect(widget.mapTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(OnFrameSelected(QModelIndex)));
	connect(widget.showAll, SIGNAL(clicked()), this, SLOT(OnShowAllChanged()));
	connect(widget.texturesListWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(OnTextureSelected(QModelIndex)));
	connect(widget.splitter, SIGNAL(splitterMoved(int, int)), this, SLOT(OnSplitterMoved(int, int)));
	connect(widget.fastEdit, SIGNAL(textEdited(QString)), this, SLOT(OnFastEditorChanged(QString)));
	connect(widget.fastEdit, SIGNAL(cursorPositionChanged(int, int)), this, SLOT(OnFastEditorCursorPositionChanged(int, int)));
	connect(widget.mapTableView, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(OnShowMapContextMenu(const QPoint&)));
	connect(widget.tabWidget, SIGNAL(currentChanged(int)), this, SLOT(OnCurrentViewChanged(int)));

#ifdef USE_INVOKER
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(DelayedUpdate()));
    CreateInvoker();
    timer->start(150);
#endif

    setAttribute(Qt::WA_PaintOnScreen);
}

MappingToolWindow::~MappingToolWindow() { }

void MappingToolWindow::ShowView()
{
    this->show();

    m_IrrControl.reset(new QIrrControl(widget.renderFrame));
    m_IrrControl->setGeometry(0, 0, widget.renderFrame->width(), widget.renderFrame->height());
    m_IrrControl->setObjectName(QString::fromUtf8("IrrControlOnMapping"));
    m_IrrControl->Init();
	m_IrrControl->show();

    CallBack(EB_ON_SHOW);
}

void MappingToolWindow::HideView()
{
    this->hide();
}

const char* MappingToolWindow::DebugName() const
{
    return "MappingToolWindow";
}

void MappingToolWindow::OnOpenFileSelected()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose a mapping file to open", "", "Mapping file (*.mpf)");

    std::string arg = filename.toUtf8().data();

    if (!arg.empty())
        CallBack(ES_ON_OPEN_MAPPING_FILE, arg);
}

void MappingToolWindow::OnSaveFile()
{
    QString filename = QFileDialog::getSaveFileName(this, "Choose a mapping file to open", "", "Mapping file (*.mpf)");

    std::string arg = filename.toUtf8().data();

    if (!arg.empty())
        CallBack(ES_ON_SAVE_MAPPING_FILE, arg);
}

void MappingToolWindow::OnOpenTextureSelected()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open image", "", "Image file (*.png *.pvr)");

    std::string arg = filename.toUtf8().data();

    if (!arg.empty())
        CallBack(ES_ON_OPEN_IMAGE, arg);
}

void MappingToolWindow::OnFrameSelected(QModelIndex index)
{
	unsigned int i = index.row();

	MakeFastEditString(index);

	CallBack(ES_ON_CHANGE_SELECTED_FRAME, i);
}

void MappingToolWindow::OnShowAllChanged()
{
	bool isShow = widget.showAll->isChecked();

	CallBack(ES_ON_SHOW_ALL_FRAMES, isShow);
}

void MappingToolWindow::OnTextureSelected(QModelIndex index)
{
	unsigned int i = index.row();

	CallBack(ES_ON_CHANGE_CURRENT_TEXTURE, i);
}

void MappingToolWindow::OnFrameDataChanged(QStandardItem* item)
{
	unsigned int col = item->index().column();
	unsigned int row = item->index().row();
	const std::string value = widget.mapTableView->model()->data(item->index()).toString().toUtf8().data();

	CallBack(ES_ON_FRAME_DATA_CHANGED, row, col, value);
}

void MappingToolWindow::OnSplitterMoved(int x, int y)
{
	if (m_IrrControl)
	{
		unsigned int width = widget.renderFrame->width();
		unsigned int height = widget.renderFrame->height();

		m_IrrControl->setGeometry(0, 0, width, height);
		m_IrrControl->Resize(core::dimension2du(width, height));

		CallBack(ES_ON_RESIZE, width, height);
	}
}

IIrrControlPtr MappingToolWindow::GetControl()
{
    return m_IrrControl;
}

void MappingToolWindow::closeEvent( QCloseEvent * ev )
{
	CallBack(EB_ON_CLOSE);
}

void MappingToolWindow::resizeEvent(QResizeEvent *evt)
{
	if (m_IrrControl)
	{
		int width = widget.renderFrame->width();
		int height = widget.renderFrame->height();

		m_IrrControl->setGeometry(0, 0, width, height);
		m_IrrControl->Resize(core::dimension2du(width, height));

		CallBack(ES_ON_RESIZE, width, height);
	}
}

void MappingToolWindow::keyPressEvent(QKeyEvent *event)
{
	QModelIndex index = widget.mapTableView->currentIndex();
	OnFrameSelected(index);
}

void MappingToolWindow::DelayedUpdate()
{
#ifdef USE_INVOKER
    //LogDebug(__FUNCTION__);
    UpdateInvoker();
#endif
}

void MappingToolWindow::RefreshSpriteInfo(SpriteTexturesListConstPtr textures, SpriteFramesListConstPtr frames)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&MappingToolWindow::RefreshSpriteInfo, this, textures, frames));
    }
    else
#endif
    {
        if (textures)
        {
            QStandardItemModel *model = new QStandardItemModel();
            for (size_t i = 0; i < textures->size(); ++i)
            {
				QIcon icon;
				std::string iconPath = std::string(MEDIA_PATH) + "Icons/16x16/puzzle.png";
				icon.addFile(iconPath.c_str(), QSize(), QIcon::Normal, QIcon::Off);
                model->appendRow( new QStandardItem(icon, QString(textures->get(i).name.c_str()) ));
            }
            widget.texturesListWidget->setModel(model);
        }

        if (frames)
        {
            QStandardItemModel *model = new QStandardItemModel();
            model->setHorizontalHeaderLabels( QStringList()<<"Name"<<"Left"<<"Top"<<"Right"<<"Bottom" );
            for (size_t i = 0; i < frames->size(); ++i)
            {
                const FrameDef& frame = frames->get(i);

                std::ostringstream name, left, top, right, bottom;
                name << frame.name.c_str();
                left << frame.left;
                top << frame.top;
                right << frame.right;
                bottom << frame.bottom;
                model->setItem(i, 0, new QStandardItem(QString(name.str().c_str()) ));
                model->setItem(i, 1, new QStandardItem(QString(left.str().c_str()) ));
                model->setItem(i, 2, new QStandardItem(QString(top.str().c_str()) ));
                model->setItem(i, 3, new QStandardItem(QString(right.str().c_str()) ));
                model->setItem(i, 4, new QStandardItem(QString(bottom.str().c_str()) ));

            }
            widget.mapTableView->setModel(model);

			connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(OnFrameDataChanged(QStandardItem*)));
        }
        widget.texturesListWidget->update();
        widget.mapTableView->update();
    }
}

void MappingToolWindow::SetFrameDataChangingError(bool isSetError)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
		BeginInvoke(std::bind(&MappingToolWindow::SetFrameDataChangingError, this, isSetError));
    }
    else
#endif
    {
		QModelIndex index = widget.mapTableView->currentIndex();
		QStandardItem* item = ((QStandardItemModel*)index.model())->item(index.row(), index.column());

		if (isSetError)
		{
			item->setData(QBrush(Qt::red), Qt::BackgroundRole);
			widget.mapTableView->selectionModel()->select(index, QItemSelectionModel::Deselect);
		}
		else
		{
			item->setData(QBrush(Qt::white), Qt::BackgroundRole);
		}
	}
}

void MappingToolWindow::SetCursor(int cursor)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
		BeginInvoke(std::bind(&MappingToolWindow::SetCursor, this, cursor));
    }
    else
#endif
    {
		Qt::CursorShape cursorStyle = Qt::ArrowCursor;
		switch (cursor)
		{
		case 0:
		case 1:
			cursorStyle = Qt::ArrowCursor;
			break;
		case 2:
			cursorStyle = Qt::SizeAllCursor;
			break;
		case 3:
			cursorStyle = Qt::OpenHandCursor;
			break;
		default:
			return;
			break;
		}

		widget.renderFrame->setCursor(cursorStyle);
	}
}

void MappingToolWindow::MakeFastEditString(QModelIndex index)
{
	m_FastEditorStr = "";
	m_FastEditorRowIndex = index.row();

	const int propsNum = 5;
	std::string strDelimeter = " ";
	std::string strProps[propsNum] = {"name=", "x=", "y=", "w=", "h="};

	for (int i = 0; i < propsNum; ++i)
	{
		const std::string value = widget.mapTableView->model()->data(widget.mapTableView->model()->index(index.row(), i)).toString().toUtf8().data();

		m_FastEditorStr += (0 == i) ? "" : strDelimeter;
		m_FastEditorStr += strProps[i];
		m_FastEditorStr += value;
	}

	widget.fastEdit->setText(m_FastEditorStr.c_str());
}

void MappingToolWindow::OnFastEditorChanged(QString text)
{
	int corruptedIndx = -1;
	const int propsNum = 5;
	std::string currentString = text.toUtf8().data();
	std::string strDelimeter = " ";
	std::string strProps[propsNum] = {"name=", "x=", "y=", "w=", "h="};

	// check corruption
	for (int i = 0; i < propsNum; ++i)
	{
		std::string prop = (0 == i) ? "" : strDelimeter;
		prop += strProps[i];

		// getting changed value
		size_t beg = currentString.find(prop);
		size_t end = (i < propsNum - 1) ? currentString.find(strDelimeter + strProps[i+1]) : currentString.length();
		if (beg == std::string::npos || end == std::string::npos || end < beg)
		{
			corruptedIndx = i;
			break;
		}
		// skip properties key
		beg += prop.length();

		// Update edited cell value
		std::string oldValue = widget.mapTableView->model()->data(widget.mapTableView->model()->index(m_FastEditorRowIndex, i)).toString().toUtf8().data();
		std::string newValue = currentString.substr(beg, end - beg).c_str();
		if (newValue != oldValue)
		{
			widget.mapTableView->model()->setData(widget.mapTableView->model()->index(m_FastEditorRowIndex, i), newValue.c_str());
		}
	}

	if (-1 != corruptedIndx)
	{
		int cursorPosition = widget.fastEdit->cursorPosition();
		widget.fastEdit->setText(m_FastEditorStr.c_str());
		widget.fastEdit->setCursorPosition(cursorPosition + 1);
	}
	else
	{
		m_FastEditorStr = currentString;
	}
}

void MappingToolWindow::OnFastEditorCursorPositionChanged(int y, int x)
{
	static bool isWasHighlighted = false;
	if (widget.fastEdit->selectedText().length() > 0 || isWasHighlighted)
	{
		isWasHighlighted = false;
		return;
	}

	const int propsNum = 5;
	std::string strDelimeter = " ";
	std::string strProps[propsNum] = {"name=", "x=", "y=", "w=", "h="};

	for (int i = 0; i < propsNum; ++i)
	{
		std::string prop = strProps[i];

		size_t beg = m_FastEditorStr.find(prop);
		size_t end = (i < propsNum - 1) ? m_FastEditorStr.find(strDelimeter + strProps[i+1]) : m_FastEditorStr.length();
		if (beg != std::string::npos && end != std::string::npos)
		{
			if (beg <= (size_t)x && (size_t)x < beg + prop.length())	// if cursor is on properties key name then properties value should be highlighted
			{
				beg += prop.length();	// shift to starting value position

				widget.fastEdit->setSelection(beg, end - beg);
				isWasHighlighted = true;	// Mark that next changing value just removes highlighting
				break;
			}
		}
	}
}

void MappingToolWindow::OnShowMapContextMenu(const QPoint& pos) // this is a slot
{
	QPoint globalPos = widget.mapTableView->mapToGlobal(pos);

    QMenu contextMenu;
    contextMenu.addAction("Delete selected frame");

    QAction* selectedItem = contextMenu.exec(globalPos);
    if (selectedItem)
    {
		if (selectedItem->text() == "Delete selected frame")
		{
			QModelIndex index = widget.mapTableView->currentIndex();
			unsigned int frameIndx = (unsigned int)index.row();
			CallBack(ES_ON_REMOVE_FRAME, frameIndx);
		}
    }
}

void MappingToolWindow::OnCurrentViewChanged(int tabIndex)
{
	if (m_IrrControl)
	{
		//m_IrrControl->Init();
	}
}