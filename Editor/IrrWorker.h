#ifndef IrrWorker_h__
#    define IrrWorker_h__

#    include "EdPrec.h"

#    include <boost/thread/thread.hpp>

enum EWorkerEvents
{
    EWE_NONE = 0,
    EWE_PAUSE,
    EWE_UNPAUSE,
    EWE_STOP,
    EWE_PUSH_LEVEL_MANAGER,
    EWE_RESIZE,
    EWE_SET_FILL_COLOR
} ;

struct SWorkerEvent
{
    EWorkerEvents evt;
    void*         data;

    SWorkerEvent() : data(NULL), evt(EWE_NONE)
    {
    }

    SWorkerEvent(EWorkerEvents e) : data(NULL), evt(e)
    {
    }

    SWorkerEvent(void* pd) : data(pd), evt(EWE_NONE)
    {
    }

    SWorkerEvent(EWorkerEvents e, void* pd) : data(pd), evt(e)
    {
    }
} ;

typedef SWorkerEvent    WorkedEvent;

class WxIrrControl;
class wxWindow;

#if USE_WX_GL
class wxGLContext;
class wxGLCanvas;
#endif

class CLevelManager;

class IrrWorker
{
private:
    bool_t                  Init();
    void                    Start();

    // ONLY POINTERS HERE
    irr::IrrlichtDevice*    m_IrrDevice;
    DriverPtr               m_Driver;
    WxIrrControl*             m_Parent;

    video::SColor			m_BackgroundColor;
    bool_t					m_IsBackgroundTransparent;
    video::ITexture*		m_TransperentTexture;
    core::vector2di			m_FillDimension;
    core::vector2di			m_FillSize;

    std::queue<WorkedEvent>* m_EventsQueue;
    CLevelManager*           m_LevelMgr;


#    if USE_WX_GL
    wxGLContext*                        m_GLContext;
#    endif

private:
    bool_t                  m_Paused;
    bool_t                  m_Stop;
    void                    DescryEvent();

public:

    boost::mutex*           m_Mutex;

    INL void PushEvent(WorkedEvent evt)
    {
        if (!m_EventsQueue || !m_Mutex) return;

        boost::mutex::scoped_try_lock lock(*m_Mutex);
        m_EventsQueue->push(evt);
    }

    void CleanUp();

    IrrWorker() :
    m_Paused(FALSE),
    m_IrrDevice(NULL),
    m_Stop(FALSE),
    m_LevelMgr(NULL),
    m_BackgroundColor(255, 150, 102, 136),
    m_IsBackgroundTransparent(FALSE),
    m_TransperentTexture(NULL)
#if USE_WX_GL
    ,m_GLContext(NULL)
#endif
    {
        m_Mutex = new boost::mutex();
        m_EventsQueue = new std::queue<WorkedEvent > ();
    }

    ~IrrWorker()
    {
        /*CleanUp();*/
    }

    INL void SetParent(WxIrrControl* parent)
    {
        m_Parent = parent;
    }

    void operator() ()
    {
        if (Init())
            Start();
        else
            APP_API_ASSERT(FALSE);
    }


#    ifdef DBGMODE
    core::stringc Name;
#    endif
} ;

#endif // IrrWorker_h__
