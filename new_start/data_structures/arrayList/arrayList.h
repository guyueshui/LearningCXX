#ifndef _ARRAY_LIST_H_
#define _ARRAY_LIST_H_

#include "linearList.h"
#include <algorithm>
#include <iostream>

template<class T>
class arrayList : linearList<T>
{
    public:
        arrayList(int initialCapacity = 10);
        arrayList(const arrayList<T>&);
        ~arrayList() {delete [] element;}

        bool empty() const {return listSize == 0;}
        int size() const {return listSize;}
        T& get(int theIndex) const;
        int indexOf(const T& theElement) const;
        void erase(int theIndex);
        void insert(int theIndex, const T& theElement);
        void output(std::ostream& out) const;

        int capacity() const {return arrayLength;}

    protected:
        void checkIndex(int theIndex) const;
        T* element; // the built-in array used to store elements
        int arrayLength; // the built-in array's length
        int listSize; // the list size
};

template<class T>
void changeLength1D(T*& a, int oldLength, int newLength) {
    // if (newLength < 0)
    //     throw illegalParameterValue("new length must be >= 0");

    T* temp = new T[newLength];
    int number = std::min(oldLength,newLength);
    std::copy(a, a + number, temp);
    delete [] a;
    a = temp;
}

#endif  // _ARRAY_LIST_H_
