/*
 * File:   IrrControlBase.h
 * Author: void
 *
 * Created on September 22, 2012, 9:16 PM
 */

#ifndef IRRCONTROLBASE_H
#    define	IRRCONTROLBASE_H

#include "ThreadBase.h"
#include "LevelManager.h"
#include "IrrWorker.h"

SHARED_PTR_FORWARD(LevelManager);

class IIrrControl: public Common::Signaling
{
public:

    enum E_SIGNALS
    {
        ES_ON_START,
        ES_ON_STOP,

        ES_ON_MOUSE_MOVED,
        ES_ON_MOUSE_DOWN,
        ES_ON_MOUSE_UP,
        ES_ON_MOUSE_DBL_CLICK,
        ES_ON_MOUSE_WHEEL,

        ES_ON_KEY_DOWN
    };

    /*virtual bool_t          Init() = 0;
    virtual void            Show() = 0;
    virtual void            Start() = 0;*/
    virtual void            Pause() = 0;
    virtual void            Resume() = 0;
    virtual void            PushLevelManager(LevelManagerPtr) = 0;

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
