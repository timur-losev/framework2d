/*
 * File:   MappingToolWindowController.h
 * Author: void
 *
 * Created on September 24, 2012, 12:13 AM
 */

#ifndef MAPPINGTOOLWINDOWCONTROLLER_H
#    define	MAPPINGTOOLWINDOWCONTROLLER_H

#    include "IRegularController.h"

#include <QtCore/qnamespace.h>	// for Qt::MouseButton

SHARED_PTR_FORWARD(IMappingToolWindow);
SHARED_PTR_FORWARD(LevelManager);
SHARED_PTR_FORWARD(MappingToolLevel);

class MappingToolWindowController: public IRegularController
{
private:
    IMappingToolWindowPtr m_MappingToolView;
    LevelManagerPtr       m_LevelManager;
    MappingToolLevelPtr   m_Level;
public:
    MappingToolWindowController(IMappingToolWindowPtr view);
    ~MappingToolWindowController();

private:
    void OnOpenMappingFile(const std::string& filePath);
    void OnSaveMappingFile(const std::string& filePath);
    void OnOpenTextureFile(const std::string& filePath);

    void OnViewShowed();
	void OnViewClosed();
	void OnMouseMove(int x, int y, Qt::MouseButton button);
	void OnMouseDown(int x, int y, Qt::MouseButton button);
	void OnMouseUp(int x, int y, Qt::MouseButton button);
	void OnMouseWheel(int delta, int direction, int x, int y);
	void OnUpdateSpriteData(const CSprite* sprite);
} ;

#endif	/* MAPPINGTOOLWINDOWCONTROLLER_H */
