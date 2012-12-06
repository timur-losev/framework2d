/*
 * File:   AboutWindowController.h
 * Author: void
 *
 * Created on September 23, 2012, 7:44 PM
 */

#ifndef ABOUTWINDOWCONTROLLER_H
#    define	ABOUTWINDOWCONTROLLER_H

#    include "EdPrec.h"
#    include "IRegularController.h"
#    include "SharedPointer.h"

SHARED_PTR_FORWARD(IAboutWindow);

class AboutWindowController: public IRegularController
{
private:
    IAboutWindowPtr m_AboutWindowView;
public:
    AboutWindowController(IAboutWindowPtr view);
    ~AboutWindowController();
} ;

#endif	/* ABOUTWINDOWCONTROLLER_H */

