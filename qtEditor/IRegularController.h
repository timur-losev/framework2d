/*
 * File:   IRegularController.h
 * Author: void
 *
 * Created on September 23, 2012, 2:43 PM
 */

#ifndef IREGULARCONTROLLER_H
#    define	IREGULARCONTROLLER_H

struct IRegularView;

struct IRegularController
{
protected:
    IRegularView* m_View;
public:
    virtual IRegularView& View()
    {
        return *m_View;
    }

    virtual const IRegularView& View() const
    {
        return *m_View;
    }

    IRegularController(): m_View(nullptr) {}
    virtual ~IRegularController() {};
};

#endif	/* IREGULARCONTROLLER_H */

