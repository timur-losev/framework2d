#ifndef EdSetValuePresenter_h__
#define EdSetValuePresenter_h__

#include "IEdSetValueView.h"

class EdSetValuePresenter
{
private:
    IEdSetValueView::Ptr    m_View;

    void                    UpdateView();
    void                    AttachViewSlots();

    void                    OnOkSelected(const core::stringc&, const core::stringc&);
    void                    OnCancelSelected();
public:

    typedef boost::shared_ptr<EdSetValuePresenter> Ptr;

    EdSetValuePresenter();
    ~EdSetValuePresenter();
};

#endif // EdSetValuePresenter_h__
