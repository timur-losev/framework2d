/*
 * File:   WxIrrControl.cpp
 * Author: Timur Losev aka void
 * Email: timur.losev@gmail.com
 * Created on February 7, 2012, 12:29 AM
 */

#include "WxIrrControl.h"
#include "SIrrCreationParameters.h"
#include "EdControlHolder.h"
#include "LevelManager.h"
#include "CLogger.h"

#include <boost/thread/thread.hpp>

#if RENDER_PROVIDER == RENDER_OGLES2
#pragma comment (lib, "../../lib/GLES2x/WindowsX86/Lib/libEGL.lib")
#pragma comment (lib, "../../lib/GLES2x/WindowsX86/Lib/libGLESv2.lib")
#elif RENDER_PROVIDER == RENDER_OGLES1
#pragma comment (lib, "../../lib/GLES1x/WindowsX86/Lib/libEGL.lib")
#pragma comment (lib, "../../lib/GLES1x/WindowsX86/Lib/libgles_cm.lib")
#endif

#ifndef __WXGTK__
IMPLEMENT_DYNAMIC_CLASS(WxIrrControl, wxControl);
#else
void WxIrrControl::classInit()
{
    //weird =)
    int result = XInitThreads ();
}
#endif

#if USE_WX_GL
BEGIN_EVENT_TABLE(WxIrrControl, wxGLCanvas)
  EVT_PAINT(WxIrrControl::OnPaint)
END_EVENT_TABLE()


static int attribs[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
#endif

WxIrrControl::WxIrrControl(wxWindow* parent, wxWindowID id, wxPoint const& pos, wxSize const& size, long style, wxValidator const& validator, wxString const& name) :
#if !USE_WX_GL
    wxControl(parent, id, pos, size, wxNO_BORDER, validator, name),
#else
wxGLCanvas(parent, id, attribs, pos, size, style, name, wxNullPalette),
#endif
        m_Initialized(FALSE), m_Paused(FALSE), m_WorkerInitializationDoneFlag(FALSE)
{
#ifdef DBGMODE
    m_Worker.Name = (const char*)name.c_str();
#endif

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

WxIrrControl::~WxIrrControl()
{
}

bool_t WxIrrControl::Init()
{
    m_Worker.SetParent(this);

    m_WorkerThread = boost::thread(m_Worker);
    //m_WorkerThread.join();

    //this->Connect(ID_RENDER_TIMER, wxEVT_TIMER, wxTimerEventHandler(WxIrrControl::OnRenderTimer));
    //this->Connect(wxEVT_SIZE, wxSizeEventHandler(WxIrrControl::OnSize));
    //this->Connect(wxEVT_ERASE_BACKGROUND, wxEraseEventHandler(WxIrrControl::OnEraseBackground));
    this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(WxIrrControl::OnClose));

    this->Connect(wxEVT_MOTION, wxMouseEventHandler(WxIrrControl::OnMouseAction));

    this->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(WxIrrControl::OnMouseAction));
    this->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(WxIrrControl::OnMouseAction));

    this->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(WxIrrControl::OnMouseAction));
    this->Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(WxIrrControl::OnMouseAction));

    this->Connect(wxEVT_MIDDLE_DOWN, wxMouseEventHandler(WxIrrControl::OnMouseAction));
    this->Connect(wxEVT_MIDDLE_UP, wxMouseEventHandler(WxIrrControl::OnMouseAction));

	this->Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(WxIrrControl::OnMouseAction));
	this->Connect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(WxIrrControl::OnMouseAction));

    this->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(WxIrrControl::OnKeyAction));

#ifdef USE_WX_GL
    //this->Connect(wxEVT_PAINT, wxPaintEventHandler(WxIrrControl::OnPaint));
#endif

    EdControlHolder::getRef().PushControl(shared_from_this());

    m_Initialized = TRUE;

    return TRUE;
}

void WxIrrControl::Start()
{
    m_OnStartSignal(shared_from_this());
}

void WxIrrControl::OnSize(wxSizeEvent& evt)
{
}

void WxIrrControl::OnClose(wxCloseEvent& evt)
{
    m_Worker.PushEvent(EWE_STOP);
    APP_API_SLEEP(30); //just in case

    LogDebug("WxIrrControl::OnClose");

    G::DriverStack.pop();
	G::FontStack.pop();

    m_OnStopSignal(shared_from_this());
}

void WxIrrControl::OnMouseAction(wxMouseEvent& evt)
{
    if (evt.GetEventType() == wxEVT_MOTION)
        m_MouseMovedSignal(evt.GetX(), evt.GetY());
    else if (evt.GetEventType() == wxEVT_LEFT_DOWN /*|| evt.LeftIsDown()*/)
        m_MouseDownSignal(EMB_LEFT, evt.GetX(), evt.GetY());
    else if (evt.GetEventType() == wxEVT_MIDDLE_DOWN /*|| evt.MiddleIsDown()*/)
        m_MouseDownSignal(EMB_MIDDLE, evt.GetX(), evt.GetY());
    else if (evt.GetEventType() == wxEVT_RIGHT_DOWN /*|| evt.RightIsDown()*/)
        m_MouseDownSignal(EMB_RIGHT, evt.GetX(), evt.GetY());
    else if (evt.GetEventType() == wxEVT_RIGHT_UP)
        m_MouseUpSignal(EMB_RIGHT, evt.GetX(), evt.GetY());
    else if (evt.GetEventType() == wxEVT_MIDDLE_UP)
        m_MouseUpSignal(EMB_MIDDLE, evt.GetX(), evt.GetY());
    else if (evt.GetEventType() == wxEVT_LEFT_UP)
        m_MouseUpSignal(EMB_LEFT, evt.GetX(), evt.GetY());
	else if (evt.GetEventType() == wxEVT_LEFT_DCLICK)
		m_MouseDblClickSignal(EMB_LEFT, evt.GetX(), evt.GetY());
	else if (evt.GetEventType() == wxEVT_MOUSEWHEEL)
		m_MouseWheelSignal(evt.GetWheelDelta(), evt.GetWheelRotation(), evt.GetX(), evt.GetY());

    this->SetFocus();
}

boost::signals::connection WxIrrControl::AttachOnMouseMovedSignal( const MouseMovedSignal::slot_type& slot )
{
    return m_MouseMovedSignal.connect(slot);
}

boost::signals::connection WxIrrControl::AttachOnMouseDownSignal(const MouseDownSignal::slot_type& slot)
{
    return m_MouseDownSignal.connect(slot);
}

boost::signals::connection WxIrrControl::AttachOnMouseUpSignal( const MouseUpSignal::slot_type& slot )
{
    return m_MouseUpSignal.connect(slot);
}

boost::signals::connection WxIrrControl::AttachOnMouseDblClickSignal(const MouseDblClickSignal::slot_type& slot)
{
	return m_MouseDblClickSignal.connect(slot);
}

boost::signals::connection WxIrrControl::AttachMouseWheelSignal(const MouseWheelSignal::slot_type& slot)
{
	return m_MouseWheelSignal.connect(slot);
}

void WxIrrControl::Pause()
{
    WorkedEvent evt(EWE_PAUSE);
    m_Worker.PushEvent(evt);
}

void WxIrrControl::Resume()
{
    WorkedEvent evt(EWE_UNPAUSE);
    m_Worker.PushEvent(evt);
}

void WxIrrControl::OnInternalIdle()
{
    wxWindow::OnInternalIdle();

   //LogDebug("OnInternalIdle()");

    if (m_WorkerInitializationDoneFlag)
    {
        m_OnWorkerInitDoneSignal();
        m_WorkerInitializationDoneFlag = FALSE;
    }
}

void WxIrrControl::PushLevelManager( CLevelManager* lmgr )
{
    lmgr->SetCrossThreadCallsParams(&m_WorkerThread, m_Worker.m_Mutex);
    WorkedEvent evt(EWE_PUSH_LEVEL_MANAGER, (void*)lmgr);
    m_Worker.PushEvent(evt);
}

void WxIrrControl::Resize(int width, int height)
{
	this->SetSize(width, height);
	core::dimension2du *size = new core::dimension2du(width, height);
	WorkedEvent evt(EWE_RESIZE, (void*)size);
    m_Worker.PushEvent(evt);
}

void WxIrrControl::SetColorFill(video::SColor color)
{
	video::SColor* c = new video::SColor(color);
	WorkedEvent evt(EWE_SET_FILL_COLOR, (void*)c);
    m_Worker.PushEvent(evt);
}

boost::signals::connection WxIrrControl::AttachOnStartSignal( const OnStartSignal::slot_type& slot )
{
    return m_OnStartSignal.connect(slot);
}

boost::signals::connection WxIrrControl::AttachOnStopSignal( const OnStopSignal::slot_type& slot )
{
    return m_OnStopSignal.connect(slot);
}

boost::signals::connection WxIrrControl::AttachOnWorkerInitDoneSignal(const OnWorkerInitDoneSignal::slot_type& slot)
{
    return m_OnWorkerInitDoneSignal.connect(slot);
}

void WxIrrControl::WorkerInitialized()
{
    m_WorkerInitializationDoneFlag = TRUE;
}

void WxIrrControl::OnKeyAction( wxKeyEvent& evt )
{
    int kc = evt.GetKeyCode();
    if (evt.GetEventType() == wxEVT_KEY_DOWN)
    {
        m_OnKeyDownSignal((irr::EKEY_CODE)kc);
    }
}

#ifdef USE_WX_GL

void WxIrrControl::OnPaint(wxPaintEvent& evt)
{
    int a = 1;
    LogDebug("OnPaint");
}

#endif

boost::signals::connection WxIrrControl::AttachOnKeyDownSignal( const OnKeyDownSignal::slot_type& slot )
{
    return m_OnKeyDownSignal.connect(slot);
}
