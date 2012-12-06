/*
 * File:   AboutWindow.cpp
 * Author: void
 *
 * Created on September 23, 2012, 7:39 PM
 */
#include "EdPrec.h"
#include "AboutWindow.h"

AboutWindow::AboutWindow(QWidget* parent): QDialog(parent, Qt::Dialog)
{
    widget.setupUi(this);
}

AboutWindow::~AboutWindow() { }

void AboutWindow::ShowView()
{
    this->show();
}

void AboutWindow::HideView()
{
    this->hide();
}