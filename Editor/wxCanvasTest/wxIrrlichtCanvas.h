/*
 *  \file   wxIrrlichtCanvas.h
 *
 *  \date   Aug 25, 2010
 *  \author cheshirekow
 *  \brief
 */

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <SIrrCreationParameters.h>
#include <IrrlichtDevice.h>
#include <IVideoDriver.h>
#include <ISceneManager.h>
#include <ICameraSceneNode.h>
#include <Keycodes.h>
#include <map>

#ifndef WXIRRLICHTCANVAS_H_
#define WXIRRLICHTCANVAS_H_






/// a wx control that wraps the irrlicht engine and displays the rendered scene
class wxIrrlichtCanvas:
    public wxGLCanvas
{
    private:
        bool                                m_hasMouse;
        wxPoint                             m_lastMouse;
        wxGLContext*                        m_glcontext;
        irr::IrrlichtDevice*                m_device;
        irr::video::IVideoDriver*           m_driver;
        irr::scene::ISceneManager*          m_smgr;
        irr::scene::ICameraSceneNode*       m_camera;
        irr::SIrrlichtCreationParameters    m_params;
        int*                                m_attributes;

        static std::map<int, irr::EKEY_CODE>   s_keyMap;
        static void classInit() __attribute__((constructor));


    protected:
        virtual void onPaint( wxPaintEvent& event );
        virtual void onMouseDown( wxMouseEvent& event );
        virtual void onMouseUp( wxMouseEvent& event );
        virtual void onMouseMove( wxMouseEvent& event );
        virtual void onKeyDown( wxKeyEvent& event );
        virtual void onKeyUp( wxKeyEvent& event );
        virtual void onSetFocus( wxFocusEvent& event );
        virtual void onKillFocus( wxFocusEvent& event );
        virtual void onResize( wxSizeEvent& event );

        int* getAttributes(irr::SIrrlichtCreationParameters& params);

    public:
        wxIrrlichtCanvas(irr::SIrrlichtCreationParameters params,
                            wxWindow *parent,
               wxWindowID id = wxID_ANY,
               const int *attribList = NULL,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0,
               const wxString& name = wxGLCanvasName,
               const wxPalette& palette = wxNullPalette);

        virtual ~wxIrrlichtCanvas();

        /// creates the device (not done in constructor because X windows might
        /// not be created or properly sized yet)
        virtual void createDevice();

        /// destroys the device
        virtual void destroyDevice();

        /// renders the scene
        virtual void render();

        /// returns the scene manager for the scene that this canvas is
        /// rendering
        irr::scene::ISceneManager* getSceneManager();

        /// return the device if it's been created
        irr::IrrlichtDevice* getDevice();
};


#endif /* WXIRRLICHTCANVAS_H_ */
