#ifndef IEdSetNameForSelectionView_h__
#define IEdSetNameForSelectionView_h__

#include "EdCommon.h"

class IEdSetNameForSelectionView
{
public:
    typedef boost::shared_ptr<IEdSetNameForSelectionView> Ptr;
    typedef boost::signal<void (const core::stringc&)> OnOkSignal;
    typedef boost::signal<void ()> OnCancelSignal;

    virtual boost::signals::connection	AttachOnOkSignal(const OnOkSignal::slot_type& slot) = 0;
    virtual boost::signals::connection	AttachOnCancelSignal(const OnCancelSignal::slot_type& slot) = 0;

    virtual void Close() = 0;
    virtual void Clear() = 0;
};

#endif // IEdSetNameForSelectionView_h__
