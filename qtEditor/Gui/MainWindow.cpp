/*
 * File:   MainWindow.cpp
 * Author: void
 *
 * Created on September 22, 2012, 8:41 PM
 */

#include "EdPrec.h"
#include "MainWindow.h"
#include "QIrrControl.h"
#include <QtGui/QPushButton>

MainWindow::MainWindow()
{
    widget.setupUi(this);
}

MainWindow::~MainWindow() { }

void MainWindow::ShowView()
{
    this->show();

    m_IrrControl.reset(new QIrrControl(widget.renderFrame));
    m_IrrControl->setGeometry(0, 0, widget.renderFrame->width(), widget.renderFrame->height());
    m_IrrControl->setObjectName(QString::fromUtf8("IrrControl"));
    m_IrrControl->show();

    m_IrrControl->Init();

    connect(widget.actionAbout, SIGNAL(activated()), this, SLOT(OnAboutClicked()));
    connect(widget.actionMapping, SIGNAL(activated()), this, SLOT(OnMappingToolClicked()));
    connect(widget.actionAtlas, SIGNAL(activated()), this, SLOT(OnAtlasToolClicked()));

    CallBack(EB_ON_SHOW);
}

void MainWindow::HideView()
{
    this->hide();

    CallBack(EB_ON_CLOSE);
}

void MainWindow::OnAboutClicked()
{
    CallBack(E_ON_ABOUT_CLICKED);
}

void MainWindow::OnMappingToolClicked()
{
    CallBack(E_ON_MAPPING_TOOL_CLICKED);
}

void MainWindow::OnAtlasToolClicked()
{
    CallBack(E_ON_ATLAS_TOOL_CLICKED);
}

void MainWindow::resizeEvent(QResizeEvent *evt)
{
	if (m_IrrControl)
	{
		m_IrrControl->setGeometry(0, 0, widget.centralwidget->width(), widget.centralwidget->height());
		m_IrrControl->Resize(core::dimension2du(widget.centralwidget->width(), widget.centralwidget->height()));
	}
}

IIrrControlPtr MainWindow::GetControl()
{
    return m_IrrControl;
}
