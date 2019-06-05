#include <vector>
#include <memory>
#include <string>

// --- class template `Blob` {
template <typename T>
class Blob {
public:
    // type alias
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    // constructors
    Blob();
    Blob(std::initializer_list<T> il);
    // selectors
    size_type size() const { return data -> size(); }
    bool empty() const { return data -> empty(); }
    T& front();
    T& back();
    T& operator[](size_type i);
    const T& front() const;
    const T& back() const;
    const T& operator[](size_type i) const;
    // modifiers
    void push_back(const T& t) { data -> push_back(t); }
    void push_back(T&& t) { data -> push_back(std::move(t)); }
    void pop_back();
private:
    std::shared_ptr<std::vector<T> > data;
    void check(size_type i, const std::string& msg) const;
}; // Blob

// impl constructors
template <typename T>
Blob<T>::Blob(): 
    data(std::make_shared<std::vector<T> >() ) { }
template <typename T>
Blob<T>::Blob(std::initializer_list<T> il):
    data(std::make_shared<std::vector<T> >(il) ) { }

// impl selectors
template <typename T>
T& Blob<T>::front() {
    check(0, "front on empty Blob");
    return data -> front();
}
template <typename T>
T& Blob<T>::back() {
    check(0, "back on empty Blob");
    return data -> back();
}
template <typename T>
T& Blob<T>::operator[](size_type i) {
    check(i, "subscript out of range");
    return (*data)[i];
}
// const overload
template <typename T>
const T& Blob<T>::front() const {
    check(0, "front on empty Blob");
    return data -> front();
}
template <typename T>
const T& Blob<T>::back() const {
    check(0, "back on empty Blob");
    return data -> back();
}
template <typename T>
const T& Blob<T>::operator[](size_type i) const {
    check(i, "subscript out of range");
    return (*data)[i];
}

// impl modifiers
template <typename T>
void Blob<T>::pop_back() {
    check(0, "pop_back on empty Blob");
    data -> pop_back();
}

// impl tools
template <typename T>
void Blob<T>::check(size_type i, const std::string& msg) const {
    if (i >= data -> size())
        throw std::out_of_range(msg);
}
// --- class template `Blob` }

// --- class template `BlobPtr` {
template <typename T>
class BlobPtr {
public:
    // constructors
    BlobPtr(): curr(0) { }
    BlobPtr(Blob<T>& a, size_t sz = 0):
        wptr(a.data), curr(sz) { }
    // selectors
    T& operator*() const {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    // modifiers
    BlobPtr& operator++(); // prefix ++
    BlobPtr& operator--(); // prefix --

private:
    // if passed, return a pointer points to vector
    std::shared_ptr<std::vector<T> >
        check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<T> > wptr;
    std::size_t curr; // current location
}; // BlobPtr

// impl modifiers
template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
    auto p = check(0, "++ on empty BlobPtr");
    ++p;
    return p;
}
//////////////// to be continued...
