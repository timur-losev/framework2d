#include "IrrWorker.h"
#include "WxIrrControl.h"
#include "LevelManager.h"
#include "wx/window.h"
#include <math.h>

#ifdef __WXGTK__
extern "C"
{
#include <gtk/gtk.h>
#include <gtk/gtkwidget.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
}
#include <boost/lexical_cast.hpp>
#include <wx/stattext.h>
#include <wx/glcanvas.h>

#endif//__WXGTK__


bool_t IrrWorker::Init()
{
    boost::mutex::scoped_lock lock(*m_Mutex);

    irr::SIrrlichtCreationParameters params;

    wxSize size = m_Parent->GetSize();

#ifdef __WXGTK__

    bool iss = true;
    do
    {
        iss = true;

        iss &= m_Parent->IsShown();
        iss &= m_Parent->IsShownOnScreen();
    }
    while(!iss);

#if USE_WX_GL
    m_GLContext = new wxGLContext(m_Parent);
    m_GLContext->SetCurrent(*m_Parent);
#endif
    GtkWidget* handle = m_Parent->GetHandle();
    Window     winID  = GDK_WINDOW_XWINDOW(handle->window);
    params.WindowId = (void*)winID;
#endif

    irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL;

#if RENDER_PROVIDER == RENDER_OGLES2
    //Irrlicht must be compiled with OGLES support too
    driverType = irr::video::EDT_OGLES2;
#elif RENDER_PROVIDER == RENDER_OGLES1
    driverType = irr::video::EDT_OGLES1;
#endif

    params.DriverType = driverType;
    params.WindowSize = irr::core::dimension2di(size.GetX(), size.GetY());
    params.Doublebuffer = true;
    params.ZBufferBits = 8;
    params.Bits = 24;

    m_IrrDevice = irr::createDeviceEx(params);

    if (!m_IrrDevice)
        return FALSE;

    m_Driver = m_IrrDevice->getVideoDriver();

    G::DriverStack.push(m_Driver);

    /*gui::IGUIFont* dbgFont = m_IrrDevice->getGUIEnvironment()->getFont(MEDIA_PATH + "lucida.xml");
    if (dbgFont)
    {
        G::FontStack.push(dbgFont);
    }*/

    if (!m_Driver) return FALSE;

    m_Driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
    m_Driver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT, false);
    m_Driver->setTextureCreationFlag(irr::video::ETCF_ALLOW_NON_POWER_2, false);
    m_Driver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_16_BIT, false);

	m_TransperentTexture = m_Driver->getTexture(MEDIA_PATH + "transparent.png");
	if (m_TransperentTexture)
	{
		core::dimension2d<u32> sizeTex = m_TransperentTexture->getSize();
		core::dimension2d<u32> sizeScr = m_Driver->getScreenSize();

		m_FillDimension.X = ceil((float)sizeScr.Width / sizeTex.Width);
		m_FillDimension.Y = ceil((float)sizeScr.Height / sizeTex.Height);

		m_FillSize.X = sizeTex.Width;
		m_FillSize.Y = sizeTex.Height;
	}

    m_Parent->WorkerInitialized(); //notify observers

    return TRUE;
}

void IrrWorker::Start()
{
    while (/*m_Driver && */!m_Stop)
    {
        if (!m_Paused && m_LevelMgr)
        {
            if (!m_IrrDevice->run()) break;
#ifdef __WXGTK__
            m_Driver->beginScene(true, true, m_BackgroundColor);
#else
            m_Driver->beginScene(true, true, m_BackgroundColor);
#endif
			if (m_IsBackgroundTransparent && m_TransperentTexture)
			{
				for (int i = 0; i < m_FillDimension.X; ++i)
				{
					for (int j = 0; j < m_FillDimension.Y; ++j)
					{
						m_Driver->draw2DImage(m_TransperentTexture, core::vector2di(i * m_FillSize.X, j * m_FillSize.Y));
					}
				}
			}

            m_LevelMgr->Update(0);

            m_Driver->endScene();
        }

        DescryEvent();
    }

    CleanUp();
}

void IrrWorker::DescryEvent()
{
    if (!m_EventsQueue || !m_Mutex) return;

    while (!m_EventsQueue->empty())
    {
        WorkedEvent evt = m_EventsQueue->front();
        switch(evt.evt)
        {
        case EWE_PAUSE:
            m_Paused = TRUE;
            break;

        case EWE_UNPAUSE:
            m_Paused = FALSE;
            break;

        case EWE_STOP:
            m_Stop = TRUE;
            break;

        case EWE_PUSH_LEVEL_MANAGER:
            APP_API_ASSERT(evt.data);
            m_LevelMgr = static_cast<CLevelManager*>(evt.data);
            m_LevelMgr->Flush();
            break;

		case EWE_RESIZE:
        {
			APP_API_ASSERT(evt.data);
            core::dimension2du *data = static_cast<core::dimension2du*>(evt.data);
			m_Driver->OnResize(*data);
			APP_API_DEL(data);
        }
			break;

		case EWE_SET_FILL_COLOR:
        {
			APP_API_ASSERT(evt.data);
            video::SColor* data = static_cast<video::SColor*>(evt.data);
			m_BackgroundColor = *data;
			m_IsBackgroundTransparent = FALSE;
			if (m_BackgroundColor.getAlpha() == 0)
			{
				m_IsBackgroundTransparent = TRUE;
			}
			APP_API_DEL(data);
        }
			break;

        /*case EWE_NONE:
            //Skip
            break;*/


        default:
            APP_API_ASSERT(FALSE);
            break;
        }

        m_EventsQueue->pop();
    }
}

void IrrWorker::CleanUp()
{
    APP_API_DEL(m_Mutex);
    APP_API_DEL(m_EventsQueue);
    APP_API_DEL(m_LevelMgr);
    if (m_IrrDevice)
        m_IrrDevice->drop();
#if USE_WX_GL
    APP_API_DEL(m_GLContext);
#endif
}

