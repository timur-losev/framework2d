/*
 * File:   IrrControlBase.h
 * Author: void
 *
 * Created on September 22, 2012, 9:16 PM
 */

#ifndef IRRCONTROLBASE_H
#    define	IRRCONTROLBASE_H

#include "ThreadBase.h"
#include <QtCore/qnamespace.h>	// for Qt::MouseButton
SHARED_PTR_FORWARD(LevelManager);

class IIrrControl
{
public:

    typedef boost::signal<void (int, int, Qt::MouseButton)>     MouseEventSignal_t;
    typedef boost::signal<void (int, int, Qt::MouseButton)>     MousePressEventSignal_t;
    typedef boost::signal<void (int, int, Qt::MouseButton)>     MouseReleaseEventSignal_t;
    typedef boost::signal<void (int, int, int, int)>            MouseWheelEventSignal_t;
    typedef boost::signal<void (irr::EKEY_CODE, EButtonState)>  KeyboardEventSignal_t;

    /*enum E_SIGNALS
    {
        ES_ON_START,
        ES_ON_STOP,

        ES_ON_MOUSE_MOVED,
        ES_ON_MOUSE_DOWN,
        ES_ON_MOUSE_UP,
        ES_ON_MOUSE_DBL_CLICK,
        ES_ON_MOUSE_WHEEL,

        ES_ON_KEY_DOWN
    };*/

    /*virtual bool_t          Init() = 0;
    virtual void            Show() = 0;
    virtual void            Start() = 0;*/
    virtual void            Pause() = 0;
    virtual void            Resume() = 0;
    virtual void            PushLevelManager(LevelManagerPtr) = 0;

    virtual boost::signals::connection AttachOnMouseEventSignal(const MouseEventSignal_t::slot_type& slot) = 0;
    virtual boost::signals::connection AttachOnMousePressEventSignal(const MousePressEventSignal_t::slot_type& slot) = 0;
    virtual boost::signals::connection AttachOnMouseReleaseEventSignal(const MouseReleaseEventSignal_t::slot_type& slot) = 0;
    virtual boost::signals::connection AttachOnMouseWheelEventSignal(const MouseWheelEventSignal_t::slot_type& slot) = 0;
    virtual boost::signals::connection AttachOnKeyboardEventSignal(const KeyboardEventSignal_t::slot_type& slot) = 0;

    virtual ThreadPtr       Thread()
    {
        return nullptr;
    }

    virtual MutexPtr        Mutex()
    {
        return nullptr;
    }
};

#endif	/* IRRCONTROLBASE_H */

