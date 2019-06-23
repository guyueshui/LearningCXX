/** @DESCRIPTION
 *  `unique_ptr` is not copyable, see how compiler complain on copying or
 *  assignmenting `unique_ptr`.
 */

#include <memory>

using std::unique_ptr;

int main(int argc, char *argv[])
{
    unique_ptr<int> p1(new int(5)) ;
    unique_ptr<int> p2(p1);
    unique_ptr<int> p3;
    p3 = p1;
    return 0;
}

// 13:26: use of deleted function
// unique_ptr(const unique_ptr&) = delete;
// 15:10: use of deleted function
// unique_ptr& operator=(const unique_ptr&) = delete;
