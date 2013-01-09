#include "EdSetNameForSelectionPresenter.h"
#include "EdViewHolder.h"

EdSetNameForSelectionPresenter::EdSetNameForSelectionPresenter()
{

    m_View = EdViewHolder::getRef().SetNameForSelectionDialog();
    AttachViewSlots();
}

EdSetNameForSelectionPresenter::~EdSetNameForSelectionPresenter()
{

}

void EdSetNameForSelectionPresenter::UpdateView()
{

}

void EdSetNameForSelectionPresenter::AttachViewSlots()
{
    m_View->AttachOnOkSignal(boost::bind(&EdSetNameForSelectionPresenter::OnOkSelected, this, _1));
    m_View->AttachOnCancelSignal(boost::bind(&EdSetNameForSelectionPresenter::OnCancelSelected, this));
}

void EdSetNameForSelectionPresenter::OnOkSelected(const core::stringc&)
{
    m_View->Close();
}

void EdSetNameForSelectionPresenter::OnCancelSelected()
{
    m_View->Close();
}

