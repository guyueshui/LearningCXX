#include "StrBlob.h"

// constructors
StrBlob::StrBlob():
    data(std::make_shared<std::vector<std::string>>()) {}

StrBlob::StrBlob(std::initializer_list<std::string> il):
    data(std::make_shared<std::vector<std::string>>(il)) {}

StrBlob::StrBlob(const StrBlob& sb):
    data(sb.data) { }

StrBlob& StrBlob::operator=(const StrBlob& rhs)
{
    data = rhs.data;
    return *this;
}

// tools
void StrBlob::check(size_type i, const std::string& msg) const
{
    if (i >= data -> size())
        throw std::out_of_range(msg);
}

// selectors
//StrBlobPtr StrBlob::begin()
//{
//    check(0, "begin on empty StrBlob");
//    return StrBlobPtr(*this);
//}
//StrBlobPtr StrBlob::end()
//{
//    check(0, "end on empty StrBlob");
//    return StrBlobPtr(*this, 0 + this->size());
//}
//ConstStrBlobPtr StrBlob::begin() const
//{
//    check(0, "begin on empty StrBlob");
//    return ConstStrBlobPtr(*this);
//}
//ConstStrBlobPtr StrBlob::end() const
//{
//    check(0, "end on empty StrBlob");
//    return ConstStrBlobPtr(*this, this -> size());
//}
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
const std::string& StrBlob::operator[](size_type idx) const
{
    check(idx, "index out of range");
    return data -> at(idx);
}
std::string& StrBlob::operator[](size_type idx)
{
    return const_cast<std::string&>(
            static_cast<const StrBlob&>(*this)[idx]
            );
}
