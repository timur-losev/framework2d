/*
 * File:   IRegularView.h
 * Author: void
 *
 * Created on September 22, 2012, 11:57 PM
 */

#ifndef IREGULARVIEW_H
#    define	IREGULARVIEW_H

struct IRegularView : public Common::Signaling
{
    enum E_BASE_SIGNALS
    {
        EB_ON_SHOW = 0,
        EB_ON_CLOSE,

        E_BASE_SIGNALS_MAX

    };

    virtual void ShowView() = 0;
    virtual void HideView() = 0;

    IRegularView() {}
    virtual ~IRegularView() {}
};

#define CAST_TO_REGULAR_VIEW(__member)\
        m_View = static_cast<IRegularView*>(__member)

#endif	/* IREGULARVIEW_H */

