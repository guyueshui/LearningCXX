#include "StrBlob.h"

// constructors
StrBlob::StrBlob() 
    : data(std::make_shared<std::vector<std::string>>()) {}
StrBlob::StrBlob(std::initializer_list<std::string> il)
    : data(std::make_shared<std::vector<std::string>>(il)) {}

// tools
void StrBlob::check(size_type i, const std::string& msg) const
{
    if (i >= data -> size())
        throw std::out_of_range(msg);
}

// selectors
StrBlobPtr StrBlob::begin() const
{
    check(0, "begin on empty StrBlob");
    return StrBlobPtr(const_cast<StrBlob&>(*this), 0);
}
StrBlobPtr StrBlob::end() const
{
    check(0, "end on empty StrBlob");
    return StrBlobPtr(const_cast<StrBlob&>(*this), 0 + this->size());
}
const std::string& StrBlob::front() const {
    check(0, "front on empty StrBlob");
    return data -> front();
}
const std::string& StrBlob::back() const {
    check(0, "back on empty StrBlob");
    return data -> back();
}
// avoid duplications using const_cast
std::string& StrBlob::front()
{
    return const_cast<std::string&>(
            static_cast<const StrBlob&>(*this).front()
            );
}
std::string& StrBlob::back()
{
    return const_cast<std::string&>(
            static_cast<const StrBlob&>(*this).back()
            );
}
void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data -> pop_back();
}
