/******************************************************************************
* File:             ConstStrBlobPtr.hpp
*
* Author:           yychi  
* Created:          2019-06-24 10:12 
* Description:      Implemention of ConstStrBlobPtr.
*****************************************************************************/

#include "StrBlob.h"

ConstStrBlobPtr::ConstStrBlobPtr(const StrBlob& a,  size_t sz):
    wptr(a.data), curr(sz) { }

ConstStrBlobPtr& ConstStrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

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
