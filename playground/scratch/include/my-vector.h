/**
 * Wrote by yychi with the assistance of perplexity AI.
 * 
 * 2026/07/28
 */
#pragma once

#include <cstddef>
#include <cstdio>
#include <initializer_list>
#include <iterator>
#include <new>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace yychi {

template <typename T>
class vector {
public:
    typedef       T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    typedef       T  value_type;
    typedef       T& reference;
    typedef const T& const_reference;

public:
    vector() = default;
    vector(size_t n);
    vector(size_t n, const T& e);
    vector(std::initializer_list<T> il);

    vector(const vector& other);
    vector(vector&& other) noexcept;

    ~vector()
    {
        destroy_0(data_, size_);
        ::operator delete(data_);
        data_ = nullptr;
        size_ = capacity_ = 0;
    }

    vector& operator=(const vector& rhs);
    vector& operator=(vector&& rhs) noexcept;

    /* element access */
    reference          at(size_t pos);
    const_reference    at(size_t pos) const;

    reference          operator[](size_t pos)          { return data_[pos]; }
    const_reference    operator[](size_t pos) const    { return data_[pos]; }

    reference          front()         { return data_[0]; }
    const_reference    front() const   { return data_[0]; }

    reference          back()          {return data_[size_ - 1]; }
    const_reference    back() const    { return data_[size_ - 1]; };

    iterator           data()          { return data_; }
    const_iterator     data() const    { return data_; }

    /* iterators */
    iterator                begin()           { return data_; }
    const_iterator          begin()     const { return data_; }
    const_iterator          cbegin()    const { return data_; }

    iterator                end()             { return data_ + size_; }
    const_iterator          end()       const { return data_ + size_; }
    const_iterator          cend()      const { return data_ + size_; }

    reverse_iterator        rbegin()          { return std::reverse_iterator(end()); }
    reverse_iterator        rend()            { return std::reverse_iterator(begin()); }

    const_reverse_iterator  crbegin()   const { return std::reverse_iterator(end()); }
    const_reverse_iterator  crend()     const { return std::reverse_iterator(begin()); }

    /* capacity */
    bool    empty() const { return size_ == 0; }
    size_t  size() const { return size_; };
    void    reserve(size_t n);
    size_t  capacity() const { return capacity_; };
    void    shrink_to_fit();

    /* modifiers */
    void     clear() noexcept;
    iterator insert(const_iterator pos, const T& e) { return emplace(pos, e); }
    iterator insert(const_iterator pos, T&& e) { return emplace(pos, std::move(e)); }
    iterator insert(const_iterator pos, size_t count, const T& value);

    template <class InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last);

    iterator insert(const_iterator pos, std::initializer_list<T> il);

    template <class... Args>
    iterator emplace(const_iterator pos, Args&&... args);

    iterator erase(const_iterator pos) { return erase(pos, pos + 1); }
    iterator erase(const_iterator first, const_iterator last);
    void push_back(const T& e) { emplace_back(e); }
    /* This is a member function of class template, not a function template!
     * So here `T&&` is not a perfect-forward.
     */
    void push_back(T&& e) { emplace_back(std::move(e)); }

    template <class ...Args>
    void emplace_back(Args&& ...args);

    void pop_back();
    void resize(size_t n) { resize(n, T()); }
    void resize(size_t n, const T& e);
    void swap(vector& x) noexcept;

private:
    void destroy_0(T* buf, size_t n) {
        if (buf) {
            if constexpr (!std::is_trivially_destructible_v<T>) {
                while (n > 0) {
                    buf[--n].~T();
                }
            }
        }
    }
    void __destruct_range(T* buf, size_t beg, size_t end) {
        if (buf) {
            if constexpr (!std::is_trivially_destructible_v<T>) {
                for (size_t i = beg; i < end; ++i) {
                    buf[i].~T();
                }
            }
        }
    }
    void __destruct_range(T* buf, const_iterator first, const_iterator last) {
        __destruct_range(buf, first - begin(), last - begin());
    }
    size_t __pre_insert_range(const_iterator pos, size_t count) {
        size_t idx = pos - data_;
        if (size_ + count > capacity_) {
            reserve((size_ + count) * 2 + 1);
        }
        for (size_t i = size_; i > idx; --i) {
            new (data_ + i - 1 + count) T(std::move_if_noexcept(data_[i - 1]));
            __destruct_range(data_, i - 1, i);
        }
        return idx;
    }

    // void __resize_impl(size_t n, const T& e);

private:
    T* data_ = nullptr;;
    size_t size_ = 0;
    size_t capacity_ = 0;

};


// implements ###############################################
template <typename T>
vector<T>::vector(size_t n) {
    data_ = static_cast<T*>(::operator new(sizeof(T) * n));
    size_t i = 0;
    try {
        for (; i < n; ++i) {
            new (data_ + i) T(); // 默认构造
        }
    } catch (...) {
        destroy_0(data_, i);
        ::operator delete(data_);
        data_ = nullptr;
        throw;
    }
    size_ = capacity_ = n;
}

template <typename T>
vector<T>::vector(size_t n, const T& e) {
    // 先分配内存，不调用构造，再用 placement new 原地拷贝构造
    // operator new/delete 不会调用构造/析构函数，只管理原始内存！
    data_ = static_cast<T*>(::operator new(sizeof(T) * n));
    size_t i = 0;
    try {
        for (; i < n; ++i) {
            new (data_ + i) T(e); // 默认构造
        }
    } catch (...) {
        destroy_0(data_, i);
        ::operator delete(data_);
        data_ = nullptr;
        throw;
    }
    size_ = capacity_ = n;
}

template <typename T>
vector<T>::vector(std::initializer_list<T> il) {
    const size_t n = il.size();
    data_ = static_cast<T*>(::operator new(sizeof(T) * n));
    size_t i = 0;
    try {
        for (const auto& e : il) {
            new (data_ + i++) T(e); // 拷贝构造
        }
    } catch (...) {
        destroy_0(data_, i);
        ::operator delete(data_);
        data_ = nullptr;
        throw;
    }
    size_ = capacity_ = n;
}

template <typename T>
vector<T>::vector(const vector& other) {
    const size_t n = other.size();
    data_ = static_cast<T*>(::operator new(sizeof(T) * n));
    size_t i = 0;
    try {
        for (; i < n; ++i) {
            new (data_ + i) T(other[i]); // 默认构造
        }
    } catch (...) {
        destroy_0(data_, i);
        ::operator delete(data_);
        data_ = nullptr;
        throw;
    }
    size_ = capacity_ = n;
}

template <typename T>
vector<T>& vector<T>::operator=(const vector& other) {
    if (this != &other) {
        vector tmp(other);
        swap(tmp);
    }
    return *this;
}

template <typename T>
vector<T>::vector(vector&& other) noexcept {
    swap(other);
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& other) noexcept {
    if (this != &other) {
        destroy_0(data_, size_);
        data_ = nullptr;
        size_ = capacity_ = 0;
        swap(other);
    }
    return *this;
}

template <typename T>
void vector<T>::resize(size_t n, const T& e) {
    if (n <= size_) {
        __destruct_range(data_, n, size_);
    }
    else {
        if (n > capacity_) {
            reserve(n);
        }
        for (size_t i = size_; i < n; ++i) {
            new (data_ + i) T(e);
        }
    }
    size_ = n;
}

template <typename T>
void vector<T>::swap(vector& x) noexcept {
    std::swap(data_, x.data_);
    std::swap(size_, x.size_);
    std::swap(capacity_, x.capacity_);
}

template <typename T>
void vector<T>::clear() noexcept {
    __destruct_range(data_, 0, size_);
    size_ = 0; // 不清空 capacity
}

template <typename T>
void vector<T>::reserve(size_t n) {
    if (n <= capacity_) {
        return;
    }
    T* tmp = static_cast<T*>(::operator new(sizeof(T) * n));
    size_t i = 0;
    try {
        for (; i < size_; ++i) {
            new (tmp + i) T(std::move_if_noexcept(data_[i]));
        }
    } catch (...) {
        destroy_0(tmp, i);
        ::operator delete(tmp);
        throw;
    }
    destroy_0(data_, size_);
    ::operator delete(data_);
    data_ = tmp;
    capacity_ = n;
}

template <typename T>
void vector<T>::shrink_to_fit() {
    if (size_ >= capacity_) {
        return;
    }
    T* tmp = static_cast<T*>(::operator new(sizeof(T) * size_));
    size_t i = 0;
    try {
        for (; i < size_; ++i) {
            new (tmp + i) T(std::move_if_noexcept(data_[i]));
        }
    } catch (...) {
        destroy_0(tmp, i);
        ::operator delete(tmp);
        throw;
    }
    destroy_0(data_, size_);
    ::operator delete(data_);
    data_ = tmp;
    capacity_ = size_;
}

template <typename T>
template <class ...Args>
void vector<T>::emplace_back(Args&& ...args) {
    if (size_ >= capacity_) {
        reserve(size_ * 2 + 1);
    }
    // static_assert(size_ < capacity_, "size must be < capacity now!");
    new (data_ + size_++) T(std::forward<Args>(args)...);
}

template <typename T>
template <class... Args>
typename vector<T>::iterator
vector<T>::emplace(const_iterator pos, Args&& ...args) {
    size_t idx = pos - data_;
    if (size_ >= capacity_) {
        reserve(size_ * 2 + 1);
    }
    for (size_t i = size_; i > idx; --i) {
        new (data_ + i) T(std::move_if_noexcept(data_[i - 1]));
        __destruct_range(data_, i - 1, i);
    }
    new (data_ + idx) T(std::forward<Args>(args)...);
    ++size_;
    return data_ + idx;
}

template <typename T>
typename vector<T>::iterator
vector<T>::insert(const_iterator pos, size_t count, const T& value) {
    size_t idx = __pre_insert_range(pos, count);
    for (size_t i = idx; i < idx + count; ++i) {
        new (data_ + i) T(value); // 拷贝构造
    }
    size_ += count;
    return begin() + idx;
}

template <typename T>
typename vector<T>::iterator
vector<T>::insert(const_iterator pos, std::initializer_list<T> il) {
    size_t idx = __pre_insert_range(pos, il.size());
    size_t i = idx;
    for (const T& value : il) {
        new (data_ + i++) T(value); // 拷贝构造
    }
    size_ += il.size();
    return begin() + idx;
}

template <typename T>
template <class InputIterator>
typename vector<T>::iterator
vector<T>::insert(const_iterator pos, InputIterator first, InputIterator last) {
    size_t idx = __pre_insert_range(pos, last - first);
    size_t i = idx;
    for (InputIterator it = first; it != last; it++) {
        new (data_ + i++) T(*it);
    }
    size_ += (last - first);
    return begin() + idx;
}


template <typename T>
typename vector<T>::iterator
vector<T>::erase(const_iterator first, const_iterator last) {
    iterator F = const_cast<iterator>(first);
    iterator L = const_cast<iterator>(last);
    if (end() - L < 0) { // invalid output
        L = end();
    }
    if (L - F <= 0) { // empty range
        return F;
    }
    __destruct_range(data_, F, L);
    for (iterator dst = F, src = L; src != end(); dst++, src++) {
        new (dst) T(std::move_if_noexcept(*src));
        __destruct_range(data_, src, src + 1);
    }
    size_ -= (L - F);
    return F;
}

template <typename T>
void vector<T>::pop_back() {
    if (empty()) {
        throw "pop_back on empty vector!";
    }
    __destruct_range(data_, size_ - 1, size_);
    --size_;
}

template <typename T>
T& vector<T>::at(size_t pos) {
    if (pos >= size()) {
        throw std::out_of_range("pos " + std::to_string(pos) + " out of range");
    }
    return data_[pos];
}

template <typename T>
typename vector<T>::const_reference
vector<T>::at(size_t pos) const {
    if (pos >= size()) {
        throw std::out_of_range("pos " + std::to_string(pos) + " out of range");
    }
    return data_[pos];
}

} // namespace yychi