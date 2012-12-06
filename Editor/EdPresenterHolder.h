/*
 * File:   EdPresenterHolder.h
 * Author: Timur Losev aka void
 * Email: timur.losev@gmail.com
 * Created on February 6, 2012, 9:19 PM
 */

#ifndef EDPRESENTERHOLDER_H
#    define	EDPRESENTERHOLDER_H

#include "FSingleton.h"
#include "EdMainWndPresenter.h"
#include "EdAtlasToolWndPresenter.h"
#include "EdMappingPresenter.h"
#include "EdSetNameForSelectionPresenter.h"
#include "EdSetValuePresenter.h"

class EdPresenterHolder: public FSingleton<EdPresenterHolder>
{
private:
    EdMainWndPresenter::Ptr         m_MainWnd;
    EdAtlasToolWndPresenter::Ptr    m_AtlasToolWnd;
    EdMappingPresenter::Ptr         m_MappingWnd;
    EdSetNameForSelectionPresenter::Ptr m_SetNameDialog;
    EdSetValuePresenter::Ptr        m_SetValueDialog;
protected:
public:
    EdPresenterHolder();
    ~EdPresenterHolder();

    void                    CreateGui();

    void                    ShowMainWindow();
    void                    ShowAtlasToolDialog();
    void                    ShowMappingToolDialog();
    void                    ShowSetNameForSelectionDialog();
    void                    ShowSetValueDialog();
} ;

#endif	/* EDPRESENTERHOLDER_H */

