#pragma once

#include "IRegularController.h"

SHARED_PTR_FORWARD(IEditFrame);

class EditFrameController: public IRegularController
{
private:
    IEditFramePtr   m_EditFrameView;
protected:
public:

    EditFrameController(IEditFramePtr view);
    ~EditFrameController();

    IEditFramePtr  GetFrameView();
};