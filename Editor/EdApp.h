/*
 * File:   EdApp.h
 * Author: Timur Losev aka void
 * Email: timur.losev@gmail.com
 * Created on February 6, 2012, 12:46 AM
 */

#ifndef EDAPP_H
#    define	EDAPP_H

#include <wx/app.h>

class EdApp: public wxApp
{
private:
protected:
public:

    virtual bool OnInit();

    virtual ~EdApp();
} ;

#endif	/* EDAPP_H */

