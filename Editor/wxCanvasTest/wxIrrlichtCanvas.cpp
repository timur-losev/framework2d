/*
 *  \file   wxIrrlichtCanvas.cpp
 *
 *  \date   Aug 25, 2010
 *  \author cheshirekow
 *  \brief
 */


#include "wxIrrlichtCanvas.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <string>

extern "C"
{
#include <gtk/gtk.h>
#include <gtk/gtkwidget.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
}


#include <IFileSystem.h>
#include <IReadFile.h>
#include <IFileArchive.h>
#include <IFileSystem.h>
#include <irrlicht.h>



std::map<int, irr::EKEY_CODE>   wxIrrlichtCanvas::s_keyMap;

void wxIrrlichtCanvas::classInit()
{
    s_keyMap[WXK_UP]    = irr::KEY_UP;
    s_keyMap[WXK_DOWN]  = irr::KEY_DOWN;
    s_keyMap[WXK_LEFT]  = irr::KEY_LEFT;
    s_keyMap[WXK_RIGHT] = irr::KEY_RIGHT;
}





int* wxIrrlichtCanvas::getAttributes(irr::SIrrlichtCreationParameters& params)
{
    int* attributes = new int[21];
    int  i=0;

    attributes[i++] = WX_GL_MIN_RED;
    attributes[i++] = 4;
    attributes[i++] = WX_GL_MIN_GREEN;
    attributes[i++] = 4;
    attributes[i++] = WX_GL_MIN_BLUE;
    attributes[i++] = 4;
    attributes[i++] = WX_GL_MIN_ALPHA;
    attributes[i++] = params.WithAlphaChannel?1:0;
    attributes[i++] = WX_GL_DEPTH_SIZE;
    attributes[i++] = params.ZBufferBits;
    attributes[i++] = WX_GL_DOUBLEBUFFER;
    attributes[i++] = params.Doublebuffer?True:False;
    attributes[i++] = WX_GL_STENCIL_SIZE;
    attributes[i++] = params.Stencilbuffer?1:0;
    attributes[i++] = WX_GL_SAMPLE_BUFFERS;
    attributes[i++] = 1;
    attributes[i++] = WX_GL_SAMPLES;
    attributes[i++] = params.AntiAlias;
    attributes[i++] = WX_GL_STEREO;
    attributes[i++] = params.Stereobuffer?True:False;
    attributes[i++] = 0;

    m_attributes = attributes;

    return attributes;
}




wxIrrlichtCanvas::wxIrrlichtCanvas(irr::SIrrlichtCreationParameters params,
        wxWindow *parent,
        wxWindowID id,
        const int *attribList,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxString& name,
        const wxPalette& palette)
:
    wxGLCanvas(parent, id, attribList, pos, size, style, name, palette),
    m_hasMouse(false),
    m_glcontext(0),
    m_device(0),
    m_driver(0),
    m_smgr(0),
    m_params(params)
{
    delete [] m_attributes;

    m_lastMouse = wxGetMousePosition();

    this->Bind( wxEVT_LEFT_UP, &wxIrrlichtCanvas::onMouseDown, this );
    this->Bind( wxEVT_LEFT_DOWN, &wxIrrlichtCanvas::onMouseDown , this);
    this->Bind( wxEVT_LEFT_UP, &wxIrrlichtCanvas::onMouseUp , this);
    this->Bind( wxEVT_MIDDLE_DOWN, &wxIrrlichtCanvas::onMouseDown , this);
    this->Bind( wxEVT_MIDDLE_UP, &wxIrrlichtCanvas::onMouseUp , this);
    this->Bind( wxEVT_RIGHT_DOWN, &wxIrrlichtCanvas::onMouseDown , this);
    this->Bind( wxEVT_RIGHT_UP, &wxIrrlichtCanvas::onMouseUp , this);
    this->Bind( wxEVT_MOTION, &wxIrrlichtCanvas::onMouseMove , this);
    this->Bind( wxEVT_KEY_DOWN, &wxIrrlichtCanvas::onKeyDown , this );
    this->Bind( wxEVT_KEY_UP, &wxIrrlichtCanvas::onKeyUp , this );
    this->Bind( wxEVT_KILL_FOCUS, &wxIrrlichtCanvas::onKillFocus , this );
    this->Bind( wxEVT_SET_FOCUS, &wxIrrlichtCanvas::onSetFocus , this );
    this->Bind( wxEVT_PAINT, &wxIrrlichtCanvas::onPaint , this);
}



wxIrrlichtCanvas::~wxIrrlichtCanvas()
{
    this->Unbind( wxEVT_LEFT_DOWN, &wxIrrlichtCanvas::onMouseDown , this);
    this->Unbind( wxEVT_LEFT_UP, &wxIrrlichtCanvas::onMouseUp , this);
    this->Unbind( wxEVT_MIDDLE_DOWN, &wxIrrlichtCanvas::onMouseDown , this);
    this->Unbind( wxEVT_MIDDLE_UP, &wxIrrlichtCanvas::onMouseUp , this);
    this->Unbind( wxEVT_RIGHT_DOWN, &wxIrrlichtCanvas::onMouseDown , this);
    this->Unbind( wxEVT_RIGHT_UP, &wxIrrlichtCanvas::onMouseUp , this);
    this->Unbind( wxEVT_MOTION, &wxIrrlichtCanvas::onMouseMove , this);
    this->Unbind( wxEVT_KEY_DOWN, &wxIrrlichtCanvas::onKeyDown , this);
    this->Unbind( wxEVT_KEY_UP, &wxIrrlichtCanvas::onKeyUp , this);
    this->Unbind( wxEVT_KILL_FOCUS, &wxIrrlichtCanvas::onKillFocus , this );
    this->Unbind( wxEVT_SET_FOCUS, &wxIrrlichtCanvas::onSetFocus , this );
    this->Unbind( wxEVT_PAINT, &wxIrrlichtCanvas::onPaint , this);
}



void wxIrrlichtCanvas::onResize(wxSizeEvent &event)
{
    if(m_driver)
    {
        int w, h;
        this->GetSize(&w, &h);
    }
}


void wxIrrlichtCanvas::createDevice()
{
    // create a new gl context
    if(!m_glcontext)
        m_glcontext = new wxGLContext(this);

    if(m_device)
        return;

    // make the current gl context current so irrlicht can find it
    m_glcontext->SetCurrent(*this);

    wxSize size = GetSize();

    GtkWidget* handle   = GetHandle();
    Window  winID       = GDK_WINDOW_XWINDOW(handle->window);
    m_params.WindowId = (void*)winID;
    m_params.DriverType = irr::video::EDT_OGLES1;

    m_device = irr::createDeviceEx(m_params);

    if ( !m_device )
    {
        wxMessageBox(wxT("Could not open the irrlicht device"),
                wxT("Error"), wxOK | wxICON_ERROR, m_parent);
    }
    else
    {
        m_driver  = m_device->getVideoDriver();
        m_smgr    = m_device->getSceneManager();
    }
}


void wxIrrlichtCanvas::destroyDevice()
{
    if(m_device)
    {
        m_device->closeDevice();
        m_device->run();
        m_device->drop();
        m_device = 0;
    }
}

void wxIrrlichtCanvas::onPaint(wxPaintEvent &event)
{
    render();
    event.Skip();
}




void wxIrrlichtCanvas::onMouseDown( wxMouseEvent& event )
{
    irr::SEvent irrevent;
    irrevent.EventType = irr::EET_MOUSE_INPUT_EVENT;
    irrevent.MouseInput.X = event.m_x - m_lastMouse.x;
    irrevent.MouseInput.Y = event.m_y - m_lastMouse.y;
    m_lastMouse = event.GetPosition();
    irrevent.MouseInput.Control = event.m_controlDown;
    irrevent.MouseInput.Shift = event.m_shiftDown;

    // mouse button states
    irrevent.MouseInput.ButtonStates = event.m_leftDown ? irr::EMBSM_LEFT : 0;
    irrevent.MouseInput.ButtonStates |= event.m_rightDown ? irr::EMBSM_RIGHT : 0;
    irrevent.MouseInput.ButtonStates |= event.m_middleDown ? irr::EMBSM_MIDDLE : 0;

    // which button was actually pressed
    switch(event.GetButton())
    {
        case wxMOUSE_BTN_LEFT:
            irrevent.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
            break;

        case wxMOUSE_BTN_RIGHT:
            irrevent.MouseInput.Event = irr::EMIE_RMOUSE_PRESSED_DOWN;
            break;

        case wxMOUSE_BTN_MIDDLE:
            irrevent.MouseInput.Event = irr::EMIE_MMOUSE_PRESSED_DOWN;
            break;

        default:
            break;
    }

    m_device->postEventFromUser(irrevent);

    if(!m_hasMouse)
    {
        this->CaptureMouse();
        m_hasMouse = true;
    }

    event.Skip();
}



void wxIrrlichtCanvas::onMouseUp( wxMouseEvent& event )
{
    irr::SEvent irrevent;
    irrevent.EventType = irr::EET_MOUSE_INPUT_EVENT;
    irrevent.MouseInput.X = event.m_x - m_lastMouse.x;
    irrevent.MouseInput.Y = event.m_y - m_lastMouse.y;
    m_lastMouse = event.GetPosition();
    irrevent.MouseInput.Control = event.m_controlDown;
    irrevent.MouseInput.Shift = event.m_shiftDown;

    // mouse button states
    irrevent.MouseInput.ButtonStates = event.m_leftDown ? irr::EMBSM_LEFT : 0;
    irrevent.MouseInput.ButtonStates |= event.m_rightDown ? irr::EMBSM_RIGHT : 0;
    irrevent.MouseInput.ButtonStates |= event.m_middleDown ? irr::EMBSM_MIDDLE : 0;

    // which button was actually pressed
    switch(event.GetButton())
    {
        case wxMOUSE_BTN_LEFT:
            irrevent.MouseInput.Event = irr::EMIE_LMOUSE_LEFT_UP;
            break;

        case wxMOUSE_BTN_RIGHT:
            irrevent.MouseInput.Event = irr::EMIE_RMOUSE_LEFT_UP;
            break;

        case wxMOUSE_BTN_MIDDLE:
            irrevent.MouseInput.Event = irr::EMIE_MMOUSE_LEFT_UP;
            break;

        default:
            break;
    }

    m_device->postEventFromUser(irrevent);

    if(m_hasMouse)
    {
        this->ReleaseMouse();
        m_hasMouse = false;
    }

    event.Skip();
}





void wxIrrlichtCanvas::onMouseMove( wxMouseEvent& event )
{
    if(m_hasMouse)
    {
        irr::SEvent irrevent;
        irrevent.EventType = irr::EET_MOUSE_INPUT_EVENT;
        irrevent.MouseInput.Event = irr::EMIE_MOUSE_MOVED;
        irrevent.MouseInput.X = event.m_x - m_lastMouse.x;
        irrevent.MouseInput.Y = event.m_y - m_lastMouse.y;
        m_lastMouse = event.GetPosition();
        irrevent.MouseInput.Control = event.m_controlDown;
        irrevent.MouseInput.Shift = event.m_shiftDown;

        // mouse button states
        irrevent.MouseInput.ButtonStates = event.m_leftDown ? irr::EMBSM_LEFT : 0;
        irrevent.MouseInput.ButtonStates |= event.m_rightDown ? irr::EMBSM_RIGHT : 0;
        irrevent.MouseInput.ButtonStates |= event.m_middleDown ? irr::EMBSM_MIDDLE : 0;

        m_device->postEventFromUser(irrevent);

        if(!irrevent.MouseInput.ButtonStates)
        {
            this->ReleaseMouse();
            m_hasMouse = false;
        }

    }

    event.Skip();
}




void wxIrrlichtCanvas::onKeyDown( wxKeyEvent& event )
{
    irr::SEvent irrevent;
    irrevent.EventType = irr::EET_KEY_INPUT_EVENT;
    irrevent.KeyInput.PressedDown = true;
    irrevent.KeyInput.Key = (s_keyMap.find(event.m_keyCode) != s_keyMap.end()) ? s_keyMap[event.m_keyCode] : (irr::EKEY_CODE)(0);
    irrevent.KeyInput.Char = event.GetKeyCode();
    irrevent.KeyInput.Control = event.m_controlDown;
    irrevent.KeyInput.Shift = event.m_shiftDown;
    m_device->postEventFromUser(irrevent);

    event.Skip();
}


void wxIrrlichtCanvas::onKeyUp( wxKeyEvent& event )
{
    irr::SEvent irrevent;
    irrevent.EventType = irr::EET_KEY_INPUT_EVENT;
    irrevent.KeyInput.PressedDown = false;
    irrevent.KeyInput.Key = (s_keyMap.find(event.m_keyCode) != s_keyMap.end()) ? s_keyMap[event.m_keyCode] : (irr::EKEY_CODE)(0);
    irrevent.KeyInput.Char = event.GetKeyCode();
    irrevent.KeyInput.Control = event.m_controlDown;
    irrevent.KeyInput.Shift = event.m_shiftDown;
    m_device->postEventFromUser(irrevent);

    event.Skip();
}







void wxIrrlichtCanvas::render()
{
    if(m_glcontext && m_device && m_isShown)
    {
        m_glcontext->SetCurrent(*this);

        if(m_device->run())
        {
            m_driver->beginScene(true, true, irr::video::SColor(0, 100, 200, 100));
            m_smgr->drawAll();
            m_driver->endScene();
        }

        SwapBuffers();
    }
}



void wxIrrlichtCanvas::onKillFocus( wxFocusEvent& event )
{
    std::cout << "Lost focus" << std::endl;
    event.Skip();
}


void wxIrrlichtCanvas::onSetFocus( wxFocusEvent& event )
{
    std::cout << "Got focus" << std::endl;
    event.Skip();
}



irr::scene::ISceneManager* wxIrrlichtCanvas::getSceneManager()
{
    return m_smgr;
}


irr::IrrlichtDevice* wxIrrlichtCanvas::getDevice()
{
    return m_device;
}
