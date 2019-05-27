#include <memory>
#include <iostream>

using namespace std;

int main() {
    int *q = new int(42), *r = new int(100);
    r = q;
    /*
     * Now r is overwrite by q, and you can delete q
     * but not r, which means the memory of value 100
     * won't be able to be freed.
     */
    auto q2 = make_shared<int>(42),
         r2 = make_shared<int>(100);
    r2 = q2;
    /*
     * Now q2.cnt+1 and r2.cnt-1 and r2.cnt=0, which
     * means r2 will be freed. After that, r2 and q2
     * point to the same memory of value 42, and have
     * the reference count 2.
     */
}
