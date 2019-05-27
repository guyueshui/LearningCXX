/*
 * Just add two const member functions.
 */
#include "StrBlob.h"

class StrBlob {
    //...
public:
    //...
    std::string& front() const;
    std::string& back() const;
};
