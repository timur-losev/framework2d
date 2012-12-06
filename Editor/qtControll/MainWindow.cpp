/*
 * File:   MainWindow.cpp
 * Author: void
 *
 * Created on September 21, 2012, 11:26 PM
 */

#include <assert.h>

#include "MainWindow.h"
#include "QIrrControl.h"


MainWindow::MainWindow()
{
    widget.setupUi(this);

    m_Controll = new QIrrControll(widget.centralwidget);
    m_Controll->setGeometry(0, 0, 256, 256);

    m_Controll->setObjectName(QString::fromUtf8("Conto"));
    m_Controll->show();

    this->connect(widget.pushButton, SIGNAL(clicked()), this, SLOT(OnButton()));
}

MainWindow::~MainWindow() { }

bool MainWindow::event(QEvent* event)
{
    if (event->type() == QEvent::Show)
        m_Controll->Init();

    return QMainWindow::event(event);
}

void MainWindow::OnButton()
{
}

