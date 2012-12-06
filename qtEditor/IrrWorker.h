/*
 * File:   IrrWorker.h
 * Author: void
 *
 * Created on September 23, 2012, 6:05 PM
 */

#ifndef IRRWORKER_H
#    define	IRRWORKER_H

#    include "Noncopyable.h"

SHARED_PTR_FORWARD(LevelManager);

typedef std::lock_guard<std::mutex> lock_guard_t;
typedef std::weak_ptr<LevelManager> LevelManagerWeakPtr;

namespace irr
{
    class IrrlichtDevice;
    namespace video
    {
        class IVideoDriver;
    }
}

class IrrWorker : public Common::Noncopyable,
                   public Common::Invoker
{
private:
    irr::IrrlichtDevice*        m_Device;
    DriverPtr                   m_Driver;
    LevelManagerWeakPtr         m_LevelManager;

    MutexPtr                    m_MutexPtr;
    ThreadPtr                   m_ThreadPtr;

    MyWinId                     m_Surface;

    bool_t                      m_Stoped;
    bool_t                      m_Paused;

public:
    IrrWorker();
    ~IrrWorker();

    bool_t                  Init();
    void                    Start();
    void                    Stop();
    bool_t                  IsWorking();
    void                    Pause();
    void                    Unpause();
    void                    YourThread(ThreadPtr thread);
    void                    SetSurface(MyWinId wid);
    void                    operator() ();

    void                    PushLevelManager(LevelManagerPtr mgr);
    void                    Resize(const core::dimension2du& size);
} ;

#endif	/* IRRWORKER_H */

