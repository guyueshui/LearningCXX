/*
 * Just add two const member functions.
 */
#include "StrBlob.h"

class StrBlob {
    //...
public:
    //...
    const std::string& front() const;
    const std::string& back() const;
};
