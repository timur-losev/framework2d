
/*
 *  \file   wxIrrlichtTest.cpp
 *
 *  \date   Sep 10, 2010
 *  \author cheshirekow
 *  \brief
 */

#include <wx/frame.h>
#include <wx/app.h>
#include "wxIrrlichtCanvas.h"
#include <IVideoDriver.h>
#include <IAnimatedMesh.h>
#include <IAnimatedMeshSceneNode.h>
#include <vector3d.h>

/// timer that is used to render the scene at fixed intervals
class RenderTimer: public wxTimer
{
    private:
        wxIrrlichtCanvas* m_canvas;

    public:
        RenderTimer(wxIrrlichtCanvas* canvas):m_canvas(canvas){}
        virtual void Notify()
        {
            m_canvas->render();
        }
};




/// timer that is used to delay the device creation until we are sure the gui is
/// created and the X windows are sized
class CreationTimer : public wxTimer
{
    private:
        wxIrrlichtCanvas* m_canvas;

    public:
        CreationTimer(wxIrrlichtCanvas* canvas):m_canvas(canvas){}
        virtual void Notify()
        {
            m_canvas->createDevice();

            irr::scene::ISceneManager* smgr = m_canvas->getSceneManager();
            irr::video::IVideoDriver*  driver = smgr->getVideoDriver();

            /*irr::scene::IAnimatedMesh* mesh = smgr->getMesh("sydney.md2");
            irr::scene::IAnimatedMeshSceneNode* node =
                                    smgr->addAnimatedMeshSceneNode( mesh );

            node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            node->setMaterialTexture( 0, driver->getTexture("sydney.bmp") );*/

            irr::scene::ICameraSceneNode* cam = smgr->addCameraSceneNodeFPS();
            cam->setPosition(irr::core::vector3df(0.0f, 0.0f, -100.0f));
        }

};




/// a very simple frame that does nothing but creats a wxIrrlichtCanvas inside
/// itself
class TestFrame : public wxFrame
{
    private:
        wxIrrlichtCanvas*   m_canvas;
        RenderTimer*        m_renderTimer;
        CreationTimer*      m_creationTimer;

    public:
        TestFrame(irr::SIrrlichtCreationParameters params) :
            wxFrame(0,wxID_ANY,"Test Frame", wxDefaultPosition,
                    wxSize( 420,420 ),
                    wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxTAB_TRAVERSAL)
        {
            wxFlexGridSizer* sizer = new wxFlexGridSizer(1,1,0,0);
            m_canvas = new wxIrrlichtCanvas(params, this);
            sizer->AddGrowableRow(0);
            sizer->AddGrowableCol(0);
            sizer->SetFlexibleDirection( wxBOTH );
            sizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
            sizer->Add(m_canvas, 0, wxALL | wxEXPAND, 5);
            this->SetSizer(sizer);
            this->Layout();

            m_renderTimer = new RenderTimer(m_canvas);
            m_creationTimer = new CreationTimer(m_canvas);

            m_renderTimer->Start(20);
            m_creationTimer->Start(100, true);

            this->Bind( wxEVT_CLOSE_WINDOW, &TestFrame::onClose, this );
        }

        wxIrrlichtCanvas* getCanvas(){return m_canvas;}

        void onClose( wxCloseEvent& event )
        {
            m_renderTimer->Stop();
            m_canvas->destroyDevice();

            event.Skip();

            this->Unbind( wxEVT_CLOSE_WINDOW, &TestFrame::onClose, this );
        }

        virtual ~TestFrame(){}
};










class TestApp : public wxApp
{
    public:
        bool OnInit()
        {
            irr::SIrrlichtCreationParameters params;
            params.AntiAlias        = 18;
            params.Bits             = 32;
            params.DriverType       = irr::video::EDT_OPENGL;
            params.Fullscreen       = false;
            params.Stencilbuffer    = false;
            params.Vsync            = false;
            params.WindowSize       = irr::core::dimension2d<irr::s32 >(400, 400);
            params.IgnoreInput      = true;
            params.Doublebuffer     = true;

            TestFrame* gui = new TestFrame(params);
            this->SetTopWindow(gui);
            gui->Show(true);

            return wxApp::OnInit();
        }
};



IMPLEMENT_APP(TestApp);
