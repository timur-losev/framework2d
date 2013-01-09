#ifndef EdSetNameForSelectionPresenter_h__
#define EdSetNameForSelectionPresenter_h__

#include "IEdSetNameForSelectionView.h"

class EdSetNameForSelectionPresenter
{
private:
    IEdSetNameForSelectionView::Ptr    m_View;

    void                    UpdateView();
    void                    AttachViewSlots();

    void                    OnOkSelected(const core::stringc&);
    void                    OnCancelSelected();
public:

    typedef boost::shared_ptr<EdSetNameForSelectionPresenter> Ptr;

    EdSetNameForSelectionPresenter();
    ~EdSetNameForSelectionPresenter();
};

#endif // EdSetNameForSelectionPresenter_h__
