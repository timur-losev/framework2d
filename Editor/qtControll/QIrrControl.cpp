/*
 * File:   QIrrControll.cpp
 * Author: void
 *
 * Created on September 21, 2012, 3:05 PM
 */

#include "QIrrControl.h"
#include <QtCore/QTimer>
#include <QtCore/QTimerEvent>
#include <qt4/QtCore/qcoreevent.h>
#include <Qt/qx11info_x11.h>

#undef signals

#include <GL/glx.h>

#include <gdk/gdkx.h>
#include <irrlicht.h>
#include <assert.h>
#include <iostream>

irr::video::SExposedVideoData expdata;

Display              *dpy;
Window                xWin;
XEvent                event;
XVisualInfo          *vInfo;
XSetWindowAttributes  swa;
GLXFBConfig          *fbConfigs;
GLXContext            context;
GLXWindow             glxWin;
int                   swaMask;
int                   numReturned;
int                   swapFlag = True;

QIrrControll::QIrrControll(QWidget* parent) : QWidget(parent), m_Handle(0)
{
    m_Device = nullptr;

    /*QPalette pal = palette();
    pal.setColor(backgroundRole(), Qt::red);
    setPalette(pal);*/

    //setAttribute(Qt::WA_PaintOnScreen);
    // Indicates that the widget paints all its pixels when it receives a paint event.
    // Thus, it is not required for operations like updating, resizing, scrolling and focus changes to erase the widget before generating paint events.
    // Not sure this is required for the program to run properly, but it is here just incase.
    //setAttribute(Qt::WA_OpaquePaintEvent);
    // Widget accepts focus by both tabbing and clicking
    //setFocusPolicy(Qt::StrongFocus);
    // Not sure if this is necessary, but it was in the code I am basing this solution off of
    //setAutoFillBackground(false);
}

QIrrControll::~QIrrControll() { }

void QIrrControll::UpdateIrrlicht(irr::IrrlichtDevice* device)
{
    if (m_Device)
    {
        m_Device->getTimer()->tick();
        irr::video::SColor color (255, 200, 101, 140);
        irr::video::IVideoDriver* dr = m_Device->getVideoDriver();

        /*expdata = dr->getExposedVideoData();

        expdata.OpenGLLinux.X11Display = dpy;
        expdata.OpenGLLinux.X11Window = winId();*/

        dr->beginScene(true, true, color/*, expdata*/);
        m_Device->getSceneManager()->drawAll();
        m_Device->getVideoDriver()->endScene();
    }
}

void QIrrControll::Init()
{
    irr::SIrrlichtCreationParameters params;
    params.Bits = 32;
    params.DeviceType = irr::EIDT_X11;
    params.DriverType = irr::video::EDT_OPENGL;
    params.Doublebuffer = true;
    params.ZBufferBits = 8;

    //Window h = MakeWindow();

    params.WindowId = reinterpret_cast<void*> (winId());
    params.WindowSize.Width = width();
    params.WindowSize.Height = height();
    params.IgnoreInput = true;

    m_Device = irr::createDeviceEx(params);

    //connect(this, SIGNAL(UpdateIrrlichtQuery(IrrlichtDevice*)), this, SLOT(UpdateIrrlicht(IrrlichtDevice*)));

    startTimer(0);
}

unsigned long QIrrControll::MakeWindow()
{

    int singleBufferAttributess[] = {
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_RENDER_TYPE,   GLX_RGBA_BIT,
        GLX_RED_SIZE,      1,   /* Request a single buffered color buffer */
        GLX_GREEN_SIZE,    1,   /* with the maximum number of color bits  */
        GLX_BLUE_SIZE,     1,   /* for each component                     */
        None
    };

    int doubleBufferAttributes[] = {
        GLX_RGBA, GLX_USE_GL,
        //GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_RENDER_TYPE,   GLX_RGBA_BIT,
        GLX_DOUBLEBUFFER,  True,  /* Request a double-buffered color buffer with */
        GLX_RED_SIZE,      4,     /* the maximum number of bits per component    */
        GLX_GREEN_SIZE,    4,
        GLX_BLUE_SIZE,     4,

        None
    };


    /* Open a connection to the X server */
    dpy = XOpenDisplay( NULL );
    const QX11Info& inf = x11Info();
    //dpy = inf.display();
    assert(dpy);

    /* Request a suitable framebuffer configuration - try for a double
     ** buffered configuration first */
    fbConfigs = glXChooseFBConfig( dpy, DefaultScreen(dpy), doubleBufferAttributes, &numReturned );

    if ( fbConfigs == NULL )
    {  /* no double buffered configs available */
        fbConfigs = glXChooseFBConfig( dpy, DefaultScreen(dpy),
                                      singleBufferAttributess, &numReturned );
        swapFlag = False;
    }

    /* Create an X colormap and window with a visual matching the first
     ** returned framebuffer config */
    vInfo = glXGetVisualFromFBConfig( dpy, fbConfigs[0] );

    swa.border_pixel = 0;
    swa.event_mask = StructureNotifyMask;
    swa.colormap = XCreateColormap( dpy, RootWindow(dpy, vInfo->screen),
                                   vInfo->visual, AllocNone );

    swaMask = CWBorderPixel | CWColormap | CWEventMask;

    xWin = XCreateWindow( dpy, RootWindow(dpy, vInfo->screen), 0, 0, 256, 256,
                         0, vInfo->depth, InputOutput, vInfo->visual,
                         swaMask, &swa );


    //xWin = winId();
#if 1
    /* Create a GLX context for OpenGL rendering */
    context = glXCreateNewContext( dpy, fbConfigs[0], GLX_RGBA_TYPE,  NULL, True );

    /* Create a GLX window to associate the frame buffer configuration
     ** with the created X window */
    XWindowAttributes wa;
    XGetWindowAttributes(dpy, xWin, &wa);
    glxWin = glXCreateWindow( dpy, fbConfigs[0], xWin, NULL );

    /* Map the window to the screen, and wait for it to appear */
    XMapWindow( dpy, xWin );
    //XIfEvent( dpy, &event, WaitForNotify, (XPointer) xWin );

    /* Bind the GLX context to the Window */
    if (!glXMakeContextCurrent( dpy, glxWin, glxWin, context ))
    {
        printf("BAD\n");
        glXDestroyContext(dpy, context);
    }

    int err = glGetError();
#else
    XMapWindow( dpy, xWin );
#endif

    return xWin;
}

void QIrrControll::paintEvent(QPaintEvent* event)
{
    /*glClearColor( 1.0, 1.0, 0.0, 1.0 );
   glClear( GL_COLOR_BUFFER_BIT );

   glFlush();

    if ( swapFlag )
   glXSwapBuffers( dpy, glxWin );

   int err = glGetError();*/

    if (m_Device)
    {
        emit UpdateIrrlicht(m_Device);
    }
}

void QIrrControll::timerEvent(QTimerEvent* event)
{
    if (m_Device)
    {
        emit UpdateIrrlicht(m_Device);
    }

    event->accept();
}

void QIrrControll::resizeEvent(QResizeEvent* event) {
 }

bool QIrrControll::event(QEvent* event)
{
    if (event->type() == QEvent::ShowToParent)
    {
        m_Handle = winId();
    }

    if (event->type() == QEvent::WinIdChange)
    {
        std::cout << "Old handle " << m_Handle << std::endl;
        m_Handle = winId();
        std::cout << "New handle " << m_Handle << std::endl;

        int a = 1;
    }
    return QWidget::event(event);
}