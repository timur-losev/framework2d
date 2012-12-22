/*
* FSingleton.h
*
*  Created on: Apr 25, 2011
*      Author: void
*/

#ifndef SINGLETON_H_
#    define SINGLETON_H_

//#    include "Types.h"

namespace Common {

template <class T>
class Singleton
{
protected:
    static T*			m_Instance;
public:

    static T& getRef()
    {
        APP_API_ASSERT(m_Instance != nullptr);

        return *m_Instance;
    }

    static T* getPtr()
    {
        return m_Instance;
    }

} ;

}

#    define SINGLETON_SETUP(_class_) template<> _class_* Common::Singleton<_class_>::m_Instance = 0
#    define SINGLETON_ENABLE_THIS m_Instance = this


#endif /* SINGLETON_H_ */
