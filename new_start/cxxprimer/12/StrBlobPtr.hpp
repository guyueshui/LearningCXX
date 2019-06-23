/******************************************************************************
* File:             StrBlobPtr.h
*
* Author:           yychi  
* Created:          2019-06-23 23:34 
* Description:      Implemention of class `StrBlobPtr`
*****************************************************************************/

#include "StrBlob.h"

// ctor
StrBlobPtr::StrBlobPtr(StrBlob& a, size_t sz):
    wptr(a.data), curr(sz) { }

// APIs
std::string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}
// prefix++, return reference of incremented object
StrBlobPtr& StrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}
// operator overloads
const std::string& StrBlobPtr::operator*() const
{
    auto p = check(curr, "derefence past end");
    return (*p)[curr];
}
std::string& StrBlobPtr::operator*()
{
    return const_cast<std::string&>(
            *(static_cast<const StrBlobPtr&>(*this)) // call const version
            );
}
StrBlobPtr& StrBlobPtr::operator++()
{
    check(curr, "increment past end StrBlobPtr");
    ++curr;
    return *this;
}

// tools
std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(size_t index, const std::string& msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (index >= ret -> size())
        throw std::out_of_range(msg);
    return ret;
}
