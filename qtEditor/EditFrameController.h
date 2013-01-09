#pragma once

#include "IRegularController.h"

SHARED_PTR_FORWARD(IEditFrame);
SHARED_PTR_FORWARD(EditablePagedLevel);

class EditFrameController: public IRegularController
{
private:
    IEditFramePtr           m_EditFrameView;
    EditablePagedLevelPtr   m_CurrentLevel;

private:

    void           AttachViewSlots();
    void           OnAddNewEmptyObject();

protected:
public:

    EditFrameController(IEditFramePtr view);
    ~EditFrameController();

    void           SetCurrenLevel(EditablePagedLevelPtr);

    IEditFramePtr  GetFrameView();
};