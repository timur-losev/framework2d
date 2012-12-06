#ifndef EdControlHolder_h__
#define EdControlHolder_h__

#include "EdPrec.h"

#include "FSingleton.h"
#include "IEdControl.h"

class EdControlHolder: public FSingleton<EdControlHolder>
{
private:
    std::stack<IEdControl::Ptr> m_Controls;

    void                    OnStart(IEdControl::Ptr ctrl);
    void                    OnStop(IEdControl::Ptr ctrl);
protected:
public:

    EdControlHolder();

    void     PushControl(IEdControl::Ptr control);

};

#endif // EdControlHolder_h__
