#ifndef IEdSetValueView_h__
#define IEdSetValueView_h__

#include "EdCommon.h"

class IEdSetValueView
{
public:
    typedef boost::shared_ptr<IEdSetValueView> Ptr;
    typedef boost::signal<void (const core::stringc&, const core::stringc&)> OnOkSignal; //text field 1, text field 2
    typedef boost::signal<void (const core::stringc&, const core::stringc&)> OnValueChangedSignal; //text field 1, text field 2
    typedef boost::signal<void ()> OnCancelSignal;

    virtual boost::signals::connection	AttachOnOkSignal(const OnOkSignal::slot_type& slot) = 0;
    virtual boost::signals::connection	AttachOnCancelSignal(const OnCancelSignal::slot_type& slot) = 0;
    virtual boost::signals::connection	AttachValueChangedSignal(const OnValueChangedSignal::slot_type& slot) = 0;

    virtual void Close() = 0;
    virtual void Clear() = 0;
    virtual void Values(const core::stringc& v1, const core::stringc& v2) = 0;
    virtual void Values(float v1, float v2) = 0;
};
#endif // IEdSetValueView_h__
