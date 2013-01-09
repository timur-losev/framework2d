#ifndef PtrForwardDeclarations_h__
#define PtrForwardDeclarations_h__

#include "Ptr.h"

#define FORWARD_PTR_DECL(__classname)\
    typedef Ptr<class __classname> __classname##Ptr

#define FORWARD_PTR_DECL_S(__classname)\
    typedef Ptr<struct __classname> __classname##Ptr


#endif // PtrForwardDeclarations_h__
