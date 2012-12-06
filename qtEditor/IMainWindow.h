/*
 * File:   IMainWindow.h
 * Author: void
 *
 * Created on September 22, 2012, 9:37 PM
 */

#ifndef IMAINWINDOW_H
#    define	IMAINWINDOW_H

#    include "IRegularView.h"

class IMainWindow : public IRegularView
{
private:
protected:
public:
    enum
    {
        E_ON_ABOUT_CLICKED = E_BASE_SIGNALS_MAX,
        E_ON_MAPPING_TOOL_CLICKED,
        E_ON_ATLAS_TOOL_CLICKED
    };

} ;

#endif	/* IMAINWINDOW_H */

