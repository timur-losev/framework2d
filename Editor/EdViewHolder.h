/*
* File:   EdViewHolder.h
* Author: Timur Losev aka void
* Email: timur.losev@gmail.com
* Created on February 6, 2012, 12:52 AM
*/

#ifndef EDVIEWHOLDER_H
#    define	EDVIEWHOLDER_H

#include "FSingleton.h"
#include "IEdMainWndView.h"
#include "IEdAtlasToolWndView.h"
#include "IEdMappingToolWndView.h"
#include "IEdSetNameForSelectionView.h"
#include "IEdSetValueView.h"

class EdViewHolder: public FSingleton<EdViewHolder>
{
private:
protected:
public:
    EdViewHolder();
    ~EdViewHolder();

    void                    CreateGui();

    IEdMainWndView::Ptr	    MainWindow();
    void		            ShowMainWindow();

    IEdAtlasToolWndView::Ptr    AtlasToolDialog();
    void                        ShowAtlasToolDialog(bool_t showmodal = FALSE);

    IEdMappingToolWndView::Ptr  MappingToolDialog();
    void                        ShowMappingToolDialog(bool_t showmodal = FALSE);

    IEdSetNameForSelectionView::Ptr SetNameForSelectionDialog();
    void                            ShowSetNameForSelectionDialog(bool_t showmodal = FALSE);

    IEdSetValueView::Ptr   SetValueDialog();
    void                   ShowSetValueDialog(bool_t showmodal = FALSE);
} ;

#endif	/* EDVIEWHOLDER_H */

