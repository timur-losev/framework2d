#include "EdSetValuePresenter.h"
#include "EdViewHolder.h"

EdSetValuePresenter::EdSetValuePresenter()
{
    m_View = EdViewHolder::getRef().SetValueDialog();
    AttachViewSlots();
}

EdSetValuePresenter::~EdSetValuePresenter()
{

}

void EdSetValuePresenter::UpdateView()
{

}

void EdSetValuePresenter::AttachViewSlots()
{
    m_View->AttachOnOkSignal(boost::bind(&EdSetValuePresenter::OnOkSelected, this, _1, _2));
    m_View->AttachOnCancelSignal(boost::bind(&EdSetValuePresenter::OnCancelSelected, this));
}

void EdSetValuePresenter::OnOkSelected(const core::stringc&, const core::stringc&)
{
    m_View->Close();
}

void EdSetValuePresenter::OnCancelSelected()
{
    m_View->Close();
}

