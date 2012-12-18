#include "EdPrec.h"
#include "EditFrameController.h"
#include "IEditFrame.h"

EditFrameController::EditFrameController( IEditFramePtr view ):
    m_EditFrameView(view)
{
    m_View = CAST_TO_REGULAR_VIEW(m_EditFrameView.get());
}

EditFrameController::~EditFrameController()
{

}

IEditFramePtr EditFrameController::GetFrameView()
{
    return m_EditFrameView;
}
