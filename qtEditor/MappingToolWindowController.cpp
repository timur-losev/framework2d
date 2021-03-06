/*
 * File:   MappingToolWindowController.cpp
 * Author: void
 *
 * Created on September 24, 2012, 12:13 AM
 */

#include "EdPrec.h"
#include "MappingToolWindowController.h"

#include "IRegularView.h"
#include "IMappingToolWindow.h"
#include "IIrrControl.h"

#include "LevelManager.h"
#include "MappingToolLevel.h"
#include "LevelFile.h"

MappingToolWindowController::MappingToolWindowController(IMappingToolWindowPtr view):
m_MappingToolView(view)
{
    CAST_TO_REGULAR_VIEW(m_MappingToolView.get());

    m_View->AttachOn<std::string>(IMappingToolWindow::ES_ON_OPEN_MAPPING_FILE, std::bind(&MappingToolWindowController::OnOpenMappingFile, this, std::placeholders::_1));
    m_View->AttachOn<std::string>(IMappingToolWindow::ES_ON_SAVE_MAPPING_FILE, std::bind(&MappingToolWindowController::OnSaveMappingFile, this, std::placeholders::_1));
    m_View->AttachOn<std::string>(IMappingToolWindow::ES_ON_OPEN_IMAGE, std::bind(&MappingToolWindowController::OnOpenTextureFile, this, std::placeholders::_1));
    m_View->AttachOn(IMappingToolWindow::EB_ON_SHOW, std::bind(&MappingToolWindowController::OnViewShowed, this));
	m_View->AttachOn(IMappingToolWindow::EB_ON_CLOSE, std::bind(&MappingToolWindowController::OnViewClosed, this));
	m_View->AttachOn<unsigned int>(IMappingToolWindow::ES_ON_CHANGE_SELECTED_FRAME, std::bind(&MappingToolWindowController::OnSelectedFrameChanged, this, std::placeholders::_1));
	m_View->AttachOn<bool>(IMappingToolWindow::ES_ON_SHOW_ALL_FRAMES, std::bind(&MappingToolWindowController::OnShowAllChanged, this, std::placeholders::_1));
	m_View->AttachOn<unsigned int>(IMappingToolWindow::ES_ON_CHANGE_CURRENT_TEXTURE, std::bind(&MappingToolWindowController::OnCurrentTextureChanged, this, std::placeholders::_1));
	m_View->AttachOn<unsigned int, unsigned int, const std::string>(IMappingToolWindow::ES_ON_FRAME_DATA_CHANGED, std::bind(&MappingToolWindowController::OnFrameDataChanged, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	m_View->AttachOn<unsigned int, unsigned int>(IMappingToolWindow::ES_ON_RESIZE, std::bind(&MappingToolWindowController::OnResizeRenderPanel, this, std::placeholders::_1, std::placeholders::_2));
	m_View->AttachOn<unsigned int>(IMappingToolWindow::ES_ON_REMOVE_FRAME, std::bind(&MappingToolWindowController::OnRemoveFrame, this, std::placeholders::_1));
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
    ThreadPtr thr = control->Thread();

    m_Level->CreateInvoker(thr);

    m_LevelManager->AttachLevel(m_Level);
	m_Level->SetPreviewDimesion(core::vector2df(1.0f, 30.0f), core::vector2di(874, 788));

    control->PushLevelManager(m_LevelManager);

	control->AttachOnMouseEventSignal(boost::bind(&MappingToolWindowController::OnMouseMove, this, _1, _2, _3));
	control->AttachOnMousePressEventSignal(boost::bind(&MappingToolWindowController::OnMouseDown, this, _1, _2, _3));
	control->AttachOnMouseReleaseEventSignal(boost::bind(&MappingToolWindowController::OnMouseUp, this, _1, _2, _3));
	control->AttachOnMouseWheelEventSignal(boost::bind(&MappingToolWindowController::OnMouseWheel, this, _1, _2, _3, _4));

	m_Level->AttachOn<const SpriteInstance*>(MappingToolLevel::ES_ON_SPRITE_DATA_UPDATED_SIGNAL, std::bind(&MappingToolWindowController::OnUpdateSpriteData, this, std::placeholders::_1));
	m_Level->AttachOn<int>(MappingToolLevel::ES_ON_CHANGE_CURSOR_SIGNAL, std::bind(&MappingToolWindowController::OnChangeCursorStyle, this, std::placeholders::_1));
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

void MappingToolWindowController::OnUpdateSpriteData(const SpriteInstance* sprite)
{
    auto texturesList = sprite->GetTexturesList();
    auto framesList = sprite->GetFramesList();
	//int currentTexture = 
	m_MappingToolView->RefreshSpriteInfo(texturesList, framesList);
}

void MappingToolWindowController::OnSelectedFrameChanged(unsigned int index)
{
	if (m_Level)
	{
		m_Level->ChangeSelectedFrame(index);
	}
}

void MappingToolWindowController::OnShowAllChanged(bool isShow)
{
	if (m_Level)
	{
		m_Level->ShowHideAllSelections(isShow);
	}
}

void MappingToolWindowController::OnCurrentTextureChanged(unsigned int index)
{
	if (m_Level)
	{
		m_Level->ChangeCurrentTexture(index);
	}
}

void MappingToolWindowController::OnFrameDataChanged(unsigned int index, unsigned int prop, const std::string value)
{
	if (m_Level)
	{
		bool result = false;
		Common::Invoker::PerformCrossThreadCall(std::bind(&MappingToolLevel::ChangeFrameProperties, m_Level.get(), index, prop, value, std::ref(result)), m_Level.get(), TRUE);

		m_MappingToolView->SetFrameDataChangingError(!result);
	}
}

void MappingToolWindowController::OnChangeCursorStyle(int cursor)
{
	m_MappingToolView->SetCursor(cursor);
}

void MappingToolWindowController::OnResizeRenderPanel(unsigned int width, unsigned int height)
{
	if (m_Level)
	{
		m_Level->SetPreviewDimesion(core::position2df(0.f, 0.f), core::position2di(width, height));
	}
}

void MappingToolWindowController::OnRemoveFrame(unsigned int index)
{
	if (m_Level)
	{
		m_Level->RemoveFrame(index);
	}
}