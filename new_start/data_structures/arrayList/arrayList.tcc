/*
 *  the implementation of class arrayList
 */

#include "arrayList.h"
#include <algorithm> // where copy defined
#include <iostream>
#include <sstream>
#include <iterator> // where ostream_iterator defined

//constructor
template<class T>
arrayList<T>::arrayList(int initialCapacity) {
    // if (initialCapacity < 1) {
    //     ostringstream s;
    //     s << "Initial capacity = " << initialCapacity
    //       << " must be > 0";
    //     throw illegalParameterValue(s.str());
    // }

    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}

template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList) {
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    std::copy(theList.element, theList.element + listSize, element);
}

//ADT method
template<class T>
void arrayList<T>::checkIndex(int theIndex) const {
    // if (theIndex < 0 || theIndex >= listSize) {
    //     ostringstream s;
    //     s << "index = " << theIndex
    //       << " size = " << listSize;
    //     throw illegalIndex(s.str());
    // }
}

template<class T>
T& arrayList<T>::get(int theIndex) const {
    checkIndex(theIndex);
    return element[theIndex];
}

template<class T>
int arrayList<T>::indexOf(const T& theElement) const {
    // return the first index of theElement, -1 while it doesn't exist
    int theIndex = int(std::find(element, element + listSize, theElement) - element);

    // theElement doesn't exist
    if (theIndex == listSize) return -1;
    else return theIndex;
}

template<class T>
void arrayList<T>::erase(int theIndex) {
    checkIndex(theIndex);

    // move the elements after theIndex to theIndex
    std::copy(element + theIndex + 1, element + listSize, element + theIndex);

    element[--listSize].~T(); //release the space of last element
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement) {
    // illegal index
    // if (theIndex < 0 || theIndex > listSize) {
    //     ostringstream s;
    //     s << "index = " << theIndex
    //       << " size = " << listSize;
    //     throw illegalIndex(s.str());
    // }

    // valid index, check the length of array
    if (listSize == arrayLength) {
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    // elements after theIndex right a bit
    std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
    element[theIndex] = theElement;
    ++listSize;
}

template<class T>
void arrayList<T>::output(std::ostream& out) const {
    std::copy(element, element + listSize, std::ostream_iterator<T>(out, " "));
}

template<class T>
std::ostream& operator<<(std::ostream& out, const arrayList<T>& x) {
    x.output(out);
    return out;
}
