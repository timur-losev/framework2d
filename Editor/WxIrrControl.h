/*
 * File:   WxIrrControl.h
 * Author: Timur Losev aka void
 * Email: timur.losev@gmail.com
 * Created on February 7, 2012, 12:29 AM
 */

#ifndef WXIRRCONTROL_H
#    define	WXIRRCONTROL_H

#    include "EdPrec.h"
#    include "EdCommon.h"
#    include "IEdControl.h"

#    include "IrrWorker.h"

//#    include "Invoker.h"

#    include <wx/control.h>
#    ifdef __WXGTK__
#        include <wx/glcanvas.h>
#    endif
#    include <wx/timer.h>

class WxIrrControl :
#    if USE_WX_GL
public wxGLCanvas,
#    else
public wxControl,
#    endif
public IEdControl,
public boost::enable_shared_from_this<WxIrrControl>
{
private:
protected:
    virtual void	    OnSize(wxSizeEvent& evt);
    virtual void	    OnClose(wxCloseEvent & evt);
    virtual void	    OnMouseAction(wxMouseEvent & evt);
    virtual void            OnKeyAction(wxKeyEvent& evt);

#ifdef USE_WX_GL
    virtual void            OnPaint(wxPaintEvent& evt);
#endif

    bool_t          m_Paused;
    bool_t          m_Initialized;
    bool_t          m_WorkerInitializationDoneFlag;

    IrrWorker       m_Worker;
    boost::thread   m_WorkerThread;

public:

    typedef boost::shared_ptr<WxIrrControl> Ptr;

#    ifndef __WXGTK__
    DECLARE_DYNAMIC_CLASS(WxIrrControl);
#    else
    static void classInit() __attribute__((constructor));
#    endif
#    ifndef __WXGTK__

    WxIrrControl()
    {
    }
#    endif
    WxIrrControl(wxWindow* parent, wxWindowID id, wxPoint const& pos, wxSize const& size, long style, wxValidator const& validator, wxString const& name);
    ~WxIrrControl();

    virtual bool_t          Init();
    virtual void            Start();

    virtual void            Pause();
    virtual void            Resume();

    virtual void            OnInternalIdle();

    void                    PushLevelManager(CLevelManager* lmgr);
    void                    Resize(int width, int height);
    void		    SetColorFill(video::SColor color);

    INL bool_t              IsPaused()
    {
        return m_Paused;
    }

    INL bool_t              IsInitilized()
    {
        return m_Initialized;
    }

    void                    WorkerInitialized(); //must be called from worker only

public: //signals

    typedef boost::signal<void (IEdControl::Ptr) > OnStartSignal;
    typedef boost::signal<void (IEdControl::Ptr) > OnStopSignal;
    typedef boost::signal<void ()> OnWorkerInitDoneSignal;

    virtual boost::signals::connection AttachOnMouseMovedSignal(const MouseMovedSignal::slot_type& slot);
    virtual boost::signals::connection AttachOnMouseDownSignal(const MouseDownSignal::slot_type& slot);
    virtual boost::signals::connection AttachOnMouseUpSignal(const MouseUpSignal::slot_type& slot);
    virtual boost::signals::connection AttachOnMouseDblClickSignal(const MouseDblClickSignal::slot_type& slot);
    virtual boost::signals::connection AttachMouseWheelSignal(const MouseWheelSignal::slot_type& slot);

    virtual boost::signals::connection AttachOnKeyDownSignal(const OnKeyDownSignal::slot_type& slot);

    boost::signals::connection AttachOnStartSignal(const OnStartSignal::slot_type& slot);
    boost::signals::connection AttachOnStopSignal(const OnStopSignal::slot_type& slot);
    boost::signals::connection AttachOnWorkerInitDoneSignal(const OnWorkerInitDoneSignal::slot_type& slot);

#if USE_WX_GL
    DECLARE_EVENT_TABLE();
#endif
    
private:
    MouseMovedSignal        m_MouseMovedSignal;
    MouseDownSignal         m_MouseDownSignal;
    MouseUpSignal           m_MouseUpSignal;
    MouseDblClickSignal		m_MouseDblClickSignal;
    MouseWheelSignal		m_MouseWheelSignal;
    OnStartSignal           m_OnStartSignal;
    OnStopSignal            m_OnStopSignal;
    OnKeyDownSignal         m_OnKeyDownSignal;
    OnWorkerInitDoneSignal  m_OnWorkerInitDoneSignal;
} ;

#endif	/* WXIRRCONTROL_H */

