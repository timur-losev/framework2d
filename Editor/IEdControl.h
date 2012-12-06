#ifndef IEdControl_h__
#define IEdControl_h__

#include "EdCommon.h"

class IEdControl
{
protected:
    typedef boost::signal<void (int, int) > MouseMovedSignal; //X, Y
    typedef boost::signal<void (int, int, int) > MouseDownSignal;//Button type, X, Y
    typedef boost::signal<void (int, int, int) > MouseUpSignal;//Button type, X, Y
    typedef boost::signal<void (int, int, int) > MouseDblClickSignal;//Button type, X, Y
    typedef boost::signal<void (int, int, int, int) > MouseWheelSignal;//delta, direction rotation, x, y
    typedef boost::signal<void (irr::EKEY_CODE) > OnKeyDownSignal;
public:

    typedef boost::shared_ptr<IEdControl> Ptr;

    /*virtual bool_t          Init() = 0;
    virtual void            Show() = 0;
    virtual void            Start() = 0;*/
    virtual void            Pause() = 0;
    virtual void            Resume() = 0;

    virtual boost::signals::connection AttachOnMouseMovedSignal(const MouseMovedSignal::slot_type& slot) = 0;
    virtual boost::signals::connection AttachOnMouseDownSignal(const MouseDownSignal::slot_type& slot) = 0;
    virtual boost::signals::connection AttachOnMouseUpSignal(const MouseUpSignal::slot_type& slot) = 0;
    virtual boost::signals::connection AttachOnMouseDblClickSignal(const MouseDblClickSignal::slot_type& slot) = 0;
    virtual boost::signals::connection AttachMouseWheelSignal(const MouseWheelSignal::slot_type& slot) = 0;

    virtual boost::signals::connection AttachOnKeyDownSignal(const OnKeyDownSignal::slot_type& slot) = 0;
};

#endif // IEdControl_h__
