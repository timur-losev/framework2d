/*
 * File:   QIrrControl.cpp
 * Author: void
 *
 * Created on September 22, 2012, 9:10 PM
 */

#include "EdPrec.h"
#include "QIrrControl.h"
#include <QtCore/QEvent>
#include <QtGui/QMouseEvent>

#include "LevelManager.h"

QIrrControl::QIrrControl(QWidget* parent): QWidget(parent)
{

}

QIrrControl::~QIrrControl()
{
    Stop();
}

bool_t QIrrControl::Init()
{
    m_Worker.SetSurface(winId());

    m_WorkerThread.reset(new std::thread(std::ref(m_Worker)));

    m_Worker.YourThread(m_WorkerThread);

	setMouseTracking(true);

    return TRUE;
}

void QIrrControl::Start()
{

}

void QIrrControl::Stop()
{
    if (!m_Worker.IsWorking())
        return;

    m_Worker.Stop();

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    m_WorkerThread->detach();
}

bool QIrrControl::event(QEvent* event)
{
    if (event->type() == QEvent::Hide)
    {
        Stop();
    }

    return QWidget::event(event);
}

void QIrrControl::Pause()
{
    Common::Invoker::PerformCrossThreadCall(std::bind(&IrrWorker::Pause, &m_Worker), &m_Worker, TRUE);
}

void QIrrControl::Resume()
{
    Common::Invoker::PerformCrossThreadCall(std::bind(&IrrWorker::Unpause, &m_Worker), &m_Worker, TRUE);
}

const char* QIrrControl::DebugName() const
{
    return "QIrrControl";
}

void QIrrControl::PushLevelManager(LevelManagerPtr mgr)
{
    Common::Invoker::PerformCrossThreadCall(std::bind(&IrrWorker::PushLevelManager, &m_Worker, mgr), &m_Worker, TRUE);
}

ThreadPtr QIrrControl::Thread()
{
    return m_Worker.Thread();
}

MutexPtr QIrrControl::Mutex()
{
    return m_Worker.Mutex();
}

void QIrrControl::Resize(const core::dimension2du& size)
{
	Common::Invoker::PerformCrossThreadCall(std::bind(&IrrWorker::Resize, &m_Worker, size), &m_Worker, TRUE);
}


//*****************************************************************************
//
// Mouse events over render panel
//*****************************************************************************
void QIrrControl::mouseMoveEvent( QMouseEvent* event )
{
	CallBack(ES_ON_MOUSE_MOVED, event->x(), event->y(), event->button());
}

void QIrrControl::mousePressEvent( QMouseEvent* event )
{
	CallBack(ES_ON_MOUSE_DOWN, event->x(), event->y(), event->button());
}

void QIrrControl::mouseReleaseEvent( QMouseEvent* event )
{
	CallBack(ES_ON_MOUSE_UP, event->x(), event->y(), event->button());
}

void QIrrControl::wheelEvent(QWheelEvent *event)
{
	CallBack(ES_ON_MOUSE_WHEEL, event->delta(), (event->delta() > 0) ? 1 : -1, event->x(), event->y());
}