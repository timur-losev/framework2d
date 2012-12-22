/*
 * File:   AboutWindowController.cpp
 * Author: void
 *
 * Created on September 23, 2012, 7:44 PM
 */

#include "EdPrec.h"
#include "AboutWindowController.h"

#include "IAboutWindow.h"
#include "IRegularView.h"

AboutWindowController::AboutWindowController(IAboutWindowPtr view):
m_AboutWindowView(view)
{
    m_View = static_cast<IRegularView*>(view.get());
}

AboutWindowController::~AboutWindowController() { }

