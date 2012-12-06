/*
 * File:   MappingToolWindowController.cpp
 * Author: void
 *
 * Created on September 24, 2012, 12:13 AM
 */

#include "MappingToolWindowController.h"

#include "IRegularView.h"
#include "IMappingToolWindow.h"
#include "IIrrControl.h"

#include "LevelManager.h"
#include "MappingToolLevel.h"

MappingToolWindowController::MappingToolWindowController(IMappingToolWindowPtr view):
m_MappingToolView(view)
{
    CAST_TO_REGULAR_VIEW(m_MappingToolView.get());

    using namespace std::placeholders;

    m_View->AttachOn<std::string>(IMappingToolWindow::ES_ON_OPEN_MAPPING_FILE, std::bind(&MappingToolWindowController::OnOpenMappingFile, this, _1));
    m_View->AttachOn<std::string>(IMappingToolWindow::ES_ON_SAVE_MAPPING_FILE, std::bind(&MappingToolWindowController::OnSaveMappingFile, this, _1));
    m_View->AttachOn<std::string>(IMappingToolWindow::ES_ON_OPEN_IMAGE, std::bind(&MappingToolWindowController::OnOpenTextureFile, this, _1));
    m_View->AttachOn(IMappingToolWindow::EB_ON_SHOW, std::bind(&MappingToolWindowController::OnViewShowed, this));
	m_View->AttachOn(IMappingToolWindow::EB_ON_CLOSE, std::bind(&MappingToolWindowController::OnViewClosed, this));

}

MappingToolWindowController::~MappingToolWindowController()
{

}

void MappingToolWindowController::OnOpenMappingFile( const std::string& filePath )
{
	APP_API_ASSERT(m_Level);

	m_Level->LoadMapFile(filePath);
}

void MappingToolWindowController::OnSaveMappingFile( const std::string& filePath )
{

}

void MappingToolWindowController::OnOpenTextureFile( const std::string& filePath )
{

}

void MappingToolWindowController::OnViewClosed()
{
	if (m_Level)
	{
		m_Level->Destroy();
	}
}

void MappingToolWindowController::OnViewShowed()
{
    IIrrControlPtr control = m_MappingToolView->GetControl();

    m_LevelManager.reset(new LevelManager());

    m_Level.reset(new MappingToolLevel());
    ThreadPtr t = control->Thread();

    m_Level->CreateInvoker(t);

    m_LevelManager->AttachLevel(m_Level);
	m_Level->SetPreviewDimesion(core::vector2df(1.0f, 30.0f), core::vector2di(874, 788));

    control->PushLevelManager(m_LevelManager);

	using namespace std::placeholders;
	control->AttachOn<int, int, Qt::MouseButton>(IIrrControl::ES_ON_MOUSE_MOVED,
            std::bind(&MappingToolWindowController::OnMouseMove, this, _1, _2, _3));
	control->AttachOn<int, int, Qt::MouseButton>(IIrrControl::ES_ON_MOUSE_DOWN,
            std::bind(&MappingToolWindowController::OnMouseDown, this, _1, _2, _3));
	control->AttachOn<int, int, Qt::MouseButton>(IIrrControl::ES_ON_MOUSE_UP,
            std::bind(&MappingToolWindowController::OnMouseUp, this, _1, _2, _3));
	control->AttachOn<int, int, int, int>(IIrrControl::ES_ON_MOUSE_WHEEL,
            std::bind(&MappingToolWindowController::OnMouseWheel, this, _1, _2, _3, _4));

	m_Level->AttachOn<const CSprite*>(MappingToolLevel::ES_ON_SPRITE_DATA_UPDATED_SIGNAL,
            std::bind(&MappingToolWindowController::OnUpdateSpriteData, this, _1));
}

void MappingToolWindowController::OnMouseMove(int x, int y, Qt::MouseButton button)
{
	if (m_Level)
	{
		m_Level->OnMouseMove(x, y);
	}
}

void MappingToolWindowController::OnMouseDown(int x, int y, Qt::MouseButton button)
{
	if (m_Level)
	{
		EMouseButtons btn = EMB_NONE;
		if (Qt::LeftButton == button)
		{
			btn = EMB_LEFT;
		}
		else if (Qt::RightButton == button)
		{
			btn = EMB_RIGHT;
		}
		else if (Qt::MiddleButton == button)
		{
			btn = EMB_MIDDLE;
		}

		m_Level->OnMouseDown(btn, x, y);
	}
}

void MappingToolWindowController::OnMouseUp(int x, int y, Qt::MouseButton button)
{
	if (m_Level)
	{
		EMouseButtons btn = EMB_NONE;
		if (Qt::LeftButton == button)
		{
			btn = EMB_LEFT;
		}
		else if (Qt::RightButton == button)
		{
			btn = EMB_RIGHT;
		}
		else if (Qt::MiddleButton == button)
		{
			btn = EMB_MIDDLE;
		}

		m_Level->OnMouseUp(btn, x, y);
	}
}

void MappingToolWindowController::OnMouseWheel(int delta, int direction, int x, int y)
{
	if (m_Level)
	{
		m_Level->SetMapViewerScale((direction > 0) ? 1.1f : 0.9f, x, y);
	}
}

void MappingToolWindowController::OnUpdateSpriteData(const CSprite* sprite)
{
    auto testuresList = sprite->GetTexturesList();
    auto framesList = sprite->GetFramesList();
	m_MappingToolView->RefreshSpriteInfo(testuresList, framesList);
}