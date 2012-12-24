/*
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

    connect(actionClose, SIGNAL(activated()), this, SLOT(close()));
    connect(actionOpenFile, SIGNAL(activated()), this, SLOT(OnOpenFileSelected()));
    connect(actionSaveFile, SIGNAL(activated()), this, SLOT(OnSaveFile()));
    connect(actionOpenTexture, SIGNAL(activated()), this, SLOT(OnOpenTextureSelected()));
	connect(widget.mapTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(OnFrameSelected(QModelIndex)));
	connect(widget.showAll, SIGNAL(clicked()), this, SLOT(OnShowAllChanged()));
	connect(widget.texturesListWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(OnTextureSelected(QModelIndex)));

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
    m_IrrControl->show();
    m_IrrControl->Init();

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
		m_IrrControl->setGeometry(0, 0, widget.renderFrame->width(), widget.renderFrame->height());
		m_IrrControl->Resize(core::dimension2du(widget.renderFrame->width(), widget.renderFrame->height()));
	}
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
                model->appendRow( new QStandardItem(QIcon("Media/Icons/16x16/puzzle.png"), QString(textures->get(i).name.c_str()) ));
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