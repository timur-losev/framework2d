/*
 * File:   SharedPtr.h
 * Author: void
 *
 * Created on September 23, 2012, 12:26 PM
 */

#ifndef SHAREDPTR_H
#    define	SHAREDPTR_H

#include <memory>

#define SHARED_PTR_FORWARD(__class__)\
class __class__;\
typedef std::shared_ptr<__class__> __class__##Ptr;\
typedef std::shared_ptr<__class__ const> __class__##ConstPtr\

#define SHARED_PTR_FORWARD_S(__class__)\
struct __class__;\
typedef std::shared_ptr<__class__> __class__##Ptr;\
typedef std::shared_ptr<__class__ const> __class__##ConstPtr\

#endif	/* SHAREDPTR_H */

