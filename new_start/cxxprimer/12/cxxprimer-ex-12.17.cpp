/** @DESCRIPTION
 *  Is the following declaration or definition appropriate.
 */

#include <memory>

using std::unique_ptr;

int ix = 1024, *pi = &ix, *pi2 = new int(2048);
typedef unique_ptr<int> IntP;
// (a)
IntP p0(ix); // wrong, cannot convert int to unique_ptr<int>
// (b)
IntP p1(pi); // maynot deconstructor p1, since by default it use `delete`,
             // but we cannot delete a built-in pointer, may need custom
             // deletor
// (c)
IntP p2(pi2); // right
// (d)
IntP p3(&ix); // same as (b)
// (e)
IntP p4(new int(2048)); // right
// (f)
IntP p5(p2.get()); // p5 and p2 manage same resources, may cause conflict
