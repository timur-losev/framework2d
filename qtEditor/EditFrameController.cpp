#include "EdPrec.h"
#include "EditFrameController.h"
#include "EditablePagedLevel.h"
#include "IEditFrame.h"

EditFrameController::EditFrameController( IEditFramePtr view ):
    m_EditFrameView(view)
{
    CAST_TO_REGULAR_VIEW(m_EditFrameView.get());

    AttachViewSlots();
}

EditFrameController::~EditFrameController()
{

}

IEditFramePtr EditFrameController::GetFrameView()
{
    return m_EditFrameView;
}

void EditFrameController::SetCurrenLevel(EditablePagedLevelPtr lvl)
{
    m_CurrentLevel = lvl;
}

void EditFrameController::AttachViewSlots()
{
    m_EditFrameView->AttachOn(IEditFrame::ES_ON_ADD_EMPTY_OBJECT, std::bind(&EditFrameController::OnAddNewEmptyObject, this));
}

void EditFrameController::OnAddNewEmptyObject()
{
    std::string name;
    Common::Invoker::PerformCrossThreadCall(std::bind(&EditablePagedLevel::AddEmptyObject, m_CurrentLevel, &name), m_CurrentLevel.get(), TRUE);

}