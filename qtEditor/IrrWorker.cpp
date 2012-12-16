/*
 * File:   IrrWorker.cpp
 * Author: void
 *
 * Created on September 23, 2012, 6:05 PM
 */

#include "EdPrec.h"
#include "IrrWorker.h"
#include "LevelManager.h"

IrrWorker::IrrWorker():
        m_Device(nullptr),
        m_Driver(nullptr),
        m_Stoped(FALSE),
        m_Paused(FALSE)

{
    m_MutexPtr.reset(new Mutex_t());
}

IrrWorker::~IrrWorker() { }

bool_t IrrWorker::Init()
{
    lock_guard_t lock(*m_MutexPtr);

    using namespace std::chrono;

    //wait for window open
    //TODO: Make true wait
    auto end = high_resolution_clock::now() + milliseconds(300);
    do
    {
        std::this_thread::yield();
        UpdateInvoker();
    }
    while(high_resolution_clock::now() < end);

    irr::SIrrlichtCreationParameters params;

    params.WindowId = reinterpret_cast<void*>(m_Surface);
    params.DriverType = irr::video::EDT_OPENGL;
    params.Doublebuffer = true;
    params.ZBufferBits = 8;
    params.Bits = 24;

    m_Device = irr::createDeviceEx(params);

    if (!m_Device)
        return FALSE;

    m_Driver = m_Device->getVideoDriver();

    m_Context.Driver = m_Driver;

    core::stringc fontpath = std::string(MEDIA_PATH + "lucida.xml").c_str();
    irr::gui::IGUIFont* dbgFont = m_Device->getGUIEnvironment()->getFont(fontpath);
    if (dbgFont)
    {
        m_Context.DebugFont = dbgFont;
    }

    return TRUE;
}

void IrrWorker::Start()
{
    u32 timePrevFrame = 0;
    const u32 msfor30frames = 32;
    //const u32 msfor60frames = 16;

    while(FALSE == m_Stoped)
    {
        UpdateInvoker();

        if (m_Paused) continue;

        if (!m_Device->run()) break;

        u32 startTime = m_Device->getTimer()->getTime();

        irr::video::SColor color (255, 39, 0, 31);	// fill color like Ubuntu style :)
        m_Driver->beginScene(true, true, color);

        u32 timeThisFrame = m_Device->getTimer()->getTime();
        float delta = static_cast<float>(timeThisFrame - timePrevFrame);

        if (auto  mgr = m_LevelManager.lock())
            mgr->Update(delta, m_Context);

        //LogDebug("MS " << delta << " Thread= " << std::this_thread::get_id());

        m_Driver->endScene();

        timePrevFrame = timeThisFrame;

        u32 timeTaken = m_Device->getTimer()->getTime() - startTime;

        if (timeTaken < msfor30frames)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(msfor30frames - timeTaken));
        }
    }
}

void IrrWorker::YourThread(ThreadPtr thread)
{
    m_ThreadPtr = thread;

    CreateInvoker(m_ThreadPtr);
}

void IrrWorker::Stop()
{
    m_Stoped = TRUE;
}

bool_t IrrWorker::IsWorking()
{
    return !m_Stoped;
}

void IrrWorker::Pause()
{
    m_Paused = TRUE;
}

void IrrWorker::Unpause()
{
    m_Paused = FALSE;
}

void IrrWorker::SetSurface( MyWinId wid )
{
    m_Surface = wid;
}

void IrrWorker::operator()()
{
    if (Init())
        Start();
    else
        APP_API_ASSERT("Impossible to start worker thread" && FALSE);
}

void IrrWorker::PushLevelManager( LevelManagerPtr mgr )
{
    m_LevelManager = mgr;
}

void IrrWorker::Resize(const core::dimension2du& size)
{
	m_Driver->OnResize(size);
}