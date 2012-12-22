#include "Sigslot2.h"

namespace Common
{
    HasSlots::HasSlots( const HasSlots& oth ) : m_ThreadPolicy(oth.m_ThreadPolicy)
    {
        LockBlock_t lock(m_ThreadPolicy);

        for (auto& sig : oth.m_Senders)
        {
            sig->SlotDuplicate(&oth, this);
            m_Senders.insert(sig);
        }
    }

    void HasSlots::SignalConnect( ISignal* sender )
    {
        LockBlock_t lock(m_ThreadPolicy);
        m_Senders.insert(sender);
    }

    void HasSlots::SignalDisconnect( ISignal* sender )
    {
        LockBlock_t lock(m_ThreadPolicy);
        m_Senders.erase(sender);
    }

    HasSlots::~HasSlots()
    {
        DisconnectAll();
    }

    void HasSlots::DisconnectAll()
    {
        LockBlock_t lock(m_ThreadPolicy);

        for(auto& sig : m_Senders)
        {
            sig->SlotDisconnect(this);
        }

        m_Senders.clear();
    }
} //Common