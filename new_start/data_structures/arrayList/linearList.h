// an abstract class of linear list

#ifndef _LINEAR_LIST_H_
#define _LINEAR_LIST_H_

#include <iostream>

template<class T>
class linearList
{
    public:
        virtual ~linearList() {};
        virtual bool empty() const = 0;
        virtual int size() const = 0;
        virtual T& get(int theIndex) const = 0;
        virtual int indexOf(const T& theElement) const = 0;
        virtual void output(std::ostream& out) const = 0;
};

#endif // _LINEAR_LIST_H_
