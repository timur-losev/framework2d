/* 
 * File:   Noncopyable.h
 * Author: void
 *
 * Created on August 20, 2012, 11:17 PM
 */

#ifndef NONCOPYABLE_H
#    define	NONCOPYABLE_H

namespace Common
{

#ifndef _MSC_VER
    class Noncopyable
    {
    public:
        Noncopyable() = default;
        Noncopyable(Noncopyable const &) = delete;
        Noncopyable & operator=(Noncopyable const &) = delete;
    } ;
#else
    class Noncopyable
    {
    public:
        Noncopyable(){};
    private:
        Noncopyable(Noncopyable const &);
        Noncopyable & operator=(Noncopyable const &);
    } ;
#endif

}
#endif	/* NONCOPYABLE_H */

