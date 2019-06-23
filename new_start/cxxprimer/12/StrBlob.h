#ifndef STRBLOB_H
#define STRBLOB_H

#include <memory>
#include <string>
#include <vector>

class StrBlob; // declaration
class StrBlobPtr // a class for manage pointers to StrBlob
{
public:
    // ctors
    StrBlobPtr(): curr(0) { }
    StrBlobPtr(StrBlob&, size_t sz = 0);

    // APIs
    std::string& deref() const;
    StrBlobPtr& incr(); // prefix ++

    // operator overload
    std::string& operator*();
    const std::string& operator*() const;
    StrBlobPtr& operator++(); // prefix++
    bool operator!=(const StrBlobPtr& rhs) const
    {
        return rhs.curr != curr;
    }
    
private:
    std::weak_ptr<std::vector<std::string>> wptr;
    size_t curr;
    std::shared_ptr<std::vector<std::string>>
        check(size_t, const std::string&) const;
}; // StroBlobPtr

class StrBlob {
    friend StrBlobPtr::StrBlobPtr(StrBlob&, size_t);
public:
    typedef std::vector<std::string>::size_type size_type;
    // ctors
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);

    // APIs
    size_type size() const { return data -> size(); }
    bool empty() const { return data -> empty(); }

    // modifiers
    void push_back(const std::string& t) {
        data -> push_back(t);
    }
    void pop_back();

    // selectors
    StrBlobPtr begin() const;
    StrBlobPtr end() const;
    std::string& front();
    std::string& back();
    const std::string& front() const;
    const std::string& back() const;
private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string& msg) const;
}; // StrBlob

#endif // STRBLOB_H
