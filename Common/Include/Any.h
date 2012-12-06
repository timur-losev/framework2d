/* 
 * File:   Any.h
 * Author: void
 *
 * Created on August 20, 2012, 11:54 PM
 */

#ifndef ANY_H
#    define	ANY_H

#    include <iostream>
#    include <algorithm>
#    include <typeinfo>
#    include <memory>
#    include <BasicTypes.h>
#    include <sstream>

#include "AppApi.h"

namespace Common
{

    class bad_any_cast: public std::exception
    {
        std::string m_Desc;
    public:
        bad_any_cast(const std::string& desc): m_Desc(desc) {}
        const char* what() const throw() { return m_Desc.c_str(); }
    };

    class Any
    {
    private:
    protected:

        class placeholder
        {
        public: // structors

            virtual ~placeholder()
            {
            }

        public: // queries

            virtual const std::type_info& GetType() const = 0;

            virtual placeholder* Clone() const = 0;

            //virtual void WriteToStream(std::ostream& o) = 0;

        } ;

        template<typename ValueType>
        class holder : public placeholder
        {
        public: // structors

            holder(const ValueType & value)
            : held(value)
            {
            }

        public: // queries

            virtual const std::type_info & GetType() const
            {
                return typeid (ValueType);
            }

            virtual placeholder* Clone() const
            {
                return new holder(held);
            }

            /*virtual void WriteToStream(std::ostream& o)
            {
                o << held;
            }*/


        public: // representation

            ValueType held;

        } ;

        placeholder* m_Content;

        template<typename ValueType>
        friend ValueType * any_cast(Any *);

    public:

        Any() : m_Content(nullptr)
        {
        }

        virtual ~Any()
        {
            delete m_Content;
        }

        template<typename ValueType>
        explicit Any(const ValueType & value)
        : m_Content(new holder<ValueType>(value))
        {
        }

        Any(const Any & other)
        : m_Content(other.m_Content ? other.m_Content->Clone() : nullptr)
        {
        }

        bool_t IsEmpty() const
        {
            return !m_Content;
        }

        const std::type_info& GetType() const
        {
            if (m_Content)
                return m_Content->GetType();

            return typeid (void);
        }

        /*inline friend std::ostream& operator <<( std::ostream& o, const Any& v )
        {
            if (v.m_Content)
                v.m_Content->WriteToStream(o);
            return o;
        }*/

        Any& Swap(Any & rhs)
        {
            std::swap(m_Content, rhs.m_Content);
            return *this;
        }

        template<typename ValueType>
                Any& operator=(const ValueType & rhs)
        {
            Any(rhs).Swap(*this);
            return *this;
        }

        Any & operator=(const Any & rhs)
        {
            Any(rhs).Swap(*this);
            return *this;
        }
        template<typename ValueType>
        ValueType operator()() const
        {
            if (!m_Content)
            {
                throw bad_any_cast("Any::operator(). Bad cast from uninitialised Any");
            }
            else if (GetType() == typeid (ValueType))
            {
                return static_cast<Any::holder<ValueType> *> (m_Content)->held;
            }
            else
            {
                std::ostringstream str;
                str << "Any::operator(). Bad cast from type '" << GetType().name() << "' "
                        << "to '" << typeid (ValueType).name() << "'";
                throw bad_any_cast(str.str);
            }
        }
    } ;

    //any cast
    template<typename ValueType>
    ValueType * any_cast(Any * operand)
    {
        if (operand && operand->GetType() == typeid (ValueType))
        {
            return &static_cast<Any::holder<ValueType> *>(operand->m_Content)->held;
        }

        return nullptr;
    }

    template<typename ValueType>
    const ValueType * any_cast(const Any * operand)
    {
        return any_cast<ValueType> (const_cast<Any *> (operand));
    }

    template<typename ValueType>
    ValueType any_cast(const Any & operand)
    {
        const ValueType * result = any_cast<ValueType > (&operand);
        if (!result)
        {
            std::ostringstream str;
            str << "Common::any_cast. Bad cast from type '" << operand.GetType().name() << "' "
                    << "to '" << typeid (ValueType).name()<< "'";
            
            throw bad_any_cast(str.str());
        }
        return *result;
    }
} //Common

#endif	/* ANY_H */

