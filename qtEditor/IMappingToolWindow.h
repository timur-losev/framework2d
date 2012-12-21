/*
 * File:   IMappingToolWindow.h
 * Author: void
 *
 * Created on September 24, 2012, 12:14 AM
 */

#ifndef IMAPPINGTOOLWINDOW_H
#    define	IMAPPINGTOOLWINDOW_H

#include "IRegularView.h"
#include "SpriteDefs.h"

SHARED_PTR_FORWARD(LevelManager);
SHARED_PTR_FORWARD(IIrrControl);

class IMappingToolWindow: public IRegularView
{
public:
    enum E_SIGNALS
    {
        ES_ON_OPEN_IMAGE = E_BASE_SIGNALS_MAX,
        ES_ON_SAVE_MAPPING_FILE,
        ES_ON_OPEN_MAPPING_FILE,
        ES_ON_CLEAR_SELECTION,
        ES_ON_FRAME_DATA_CHANGED,
        ES_ON_ZOOM_SCROLLED,
        ES_ON_BUTTON_ADD_FRAME,
        ES_ON_BUTTON_SHOW_HIDE_FRAMES,
        ES_ON_RESIZE,
        ES_ON_CHANGE_CURRENT_TEXTURE,
        ES_ON_REMOVE_FRAME,
        ES_ON_REMOVE_TEXTURE,
        ES_ON_CHANGE_SELECTED_FRAME,
		ES_ON_SHOW_ALL_FRAMES,
    };

    virtual IIrrControlPtr GetControl() = 0;

    virtual void RefreshSpriteInfo( SpriteTexturesListConstPtr textures, SpriteFramesListConstPtr frames) = 0;
};

#endif	/* IMAPPINGTOOLWINDOW_H */

