#include "EdControlHolder.h"
#include "WxIrrControl.h"

SINGLETON_SETUP(EdControlHolder);

void EdControlHolder::PushControl( IEdControl::Ptr control )
{
    WxIrrControl* ctr = static_cast<WxIrrControl*>(control.get());
    //WxIrrControl::Ptr irrc = boost::static_pointer_cast<WxIrrControl::Ptr>(control); //TODO
    ctr->AttachOnStartSignal(boost::bind(&EdControlHolder::OnStart, this, _1));
    ctr->AttachOnStopSignal(boost::bind(&EdControlHolder::OnStop, this, _1));

    //m_Controls.push(control);
}

EdControlHolder::EdControlHolder()
{
    SINGLETON_ENABLE_THIS;
}

void EdControlHolder::OnStart( IEdControl::Ptr ctrl )
{
    if (!m_Controls.empty())
    {
        m_Controls.top()->Pause();
    }
    
    m_Controls.push(ctrl);
}

void EdControlHolder::OnStop( IEdControl::Ptr ctrl )
{
    if (m_Controls.size() > 1)
    {
        m_Controls.pop();
        m_Controls.top()->Resume();
    }
    else if (!m_Controls.empty())
    {
        m_Controls.pop();
    }
}
