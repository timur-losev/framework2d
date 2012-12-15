/*
 * File:   QIrrControl.h
 * Author: void
 *
 * Created on September 22, 2012, 9:10 PM
 */

#ifndef QIRRCONTROL_H
#    define	QIRRCONTROL_H

#    include "IIrrControl.h"

#    include <QtGui/QWidget>

#    include "IrrWorker.h"

SHARED_PTR_FORWARD(LevelManager);

class QIrrControl : public QWidget, public IIrrControl
{
    Q_OBJECT

private:
    ThreadPtr               m_WorkerThread;
    IrrWorker               m_Worker;

    MouseEventSignal_t          m_MouseEventSignal;
    MousePressEventSignal_t     m_MousePressEventSignal;
    MouseReleaseEventSignal_t   m_MouseReleaseEventSignal;
    MouseWheelEventSignal_t     m_MouseWheelEventSignal;
    KeyboardEventSignal_t       m_KeyboardEventSignal;

public:
    QIrrControl(QWidget* parent = nullptr);
    ~QIrrControl();

    virtual const char*     DebugName() const;

    bool_t                  Init();
    void                    Start();
    void                    Stop();

    bool                    event(QEvent* event);

    virtual void            Pause();
    virtual void            Resume();

    virtual ThreadPtr       Thread();
    virtual MutexPtr        Mutex();

    virtual void            PushLevelManager(LevelManagerPtr mgr);
    virtual void            Resize(const core::dimension2du& size);
    virtual void            mouseMoveEvent(QMouseEvent* event);
    virtual void            mousePressEvent (QMouseEvent* event);
    virtual void            mouseReleaseEvent (QMouseEvent* event);
    virtual void            wheelEvent(QWheelEvent *event);
    virtual void            keyPressEvent(QKeyEvent *);
    virtual void            keyReleaseEvent(QKeyEvent *);


    virtual boost::signals::connection AttachOnMouseEventSignal(const MouseEventSignal_t::slot_type& slot);
    virtual boost::signals::connection AttachOnMousePressEventSignal(const MousePressEventSignal_t::slot_type& slot);
    virtual boost::signals::connection AttachOnMouseReleaseEventSignal(const MouseReleaseEventSignal_t::slot_type& slot);
    virtual boost::signals::connection AttachOnMouseWheelEventSignal(const MouseWheelEventSignal_t::slot_type& slot);
    virtual boost::signals::connection AttachOnKeyboardEventSignal(const KeyboardEventSignal_t::slot_type& slot);
} ;

#endif	/* QIRRCONTROL_H */

