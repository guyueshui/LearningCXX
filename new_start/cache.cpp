#include <iostream>
#include <cstring>
#include <vector>
#include <forward_list>
using namespace std;

// int main(){
//     vector<string> vcs;
//     vcs.push_back("this is A");
//     vector<string>::iterator it = vcs.begin();
//     int i = 9;
//     for (; it!=vcs.end(); ++it) {
//         cout << "caplity of vector is: " << vcs.size() << endl;
//         //cout << "---> " << *it << endl;   //去掉此句会有一个超过vector
//                                    //大小的循环，高手能解释一下为什么?
//         if (i == 9) {
//             vcs.push_back("this is BBBBB");
//             cout << "vcs.push!" << endl;
//         }
//         i=8;
//     }
//     return 0;
// }

// int main(int argc, char const *argv[]) {
//     std::vector<int> ivec{0,1,2,3,4,5,6,7,8,9};
//     std::vector<int>::iterator iter = ivec.begin(),
//                                mid = ivec.begin() + ivec.size()/2;
//                                //mid = ivec.begin() + (ivec.end()-ivec.begin())/2
//
//     while (iter != mid) {
//         if (*iter == 3)
//             ivec.insert(iter,2*3);
//         iter++;
//     }
//
//     for (auto i : ivec) cout << i << ' ';
//     return 0;
// }

// int main(int argc, char const *argv[]) {
//     std::forward_list<int> iflst{0,1,2,3,4,5,6,7,8,9};
//     // auto beg = ivec.begin(), end = ivec.end();
//     // auto iter = ivec.erase(beg + 1,end);
//     // for (auto i : ivec) cout << i << ' ';
//     // cout << "\n" << *iter;
//     auto prev = iflst.before_begin();
//     auto curr = iflst.begin();
//
//     while (curr != iflst.end()) {
//         if (*curr & 1) curr = iflst.erase_after(prev);
//         else prev = curr++;
//     }
//
//     for (auto i : iflst) cout << i << ' ';
//     return 0;
// }

// int main(int argc, char const *argv[]) {
//     std::vector<int> ivec = {1,2};
//     auto iter = ivec.begin();
//     while (iter != ivec.end()) {
//         if (*iter & 1)
//             iter = ivec.insert(iter, *iter);
//         ++iter;
//     }
//
//     for (auto i : ivec) cout << i << ' ';
//     return 0;
// }

int main(int argc, char const *argv[]) {
    std::vector<int> ivec;
    cout << "size - " << ivec.size()
         << "capacity - " << ivec.capacity() << endl;
    for (vector<int>::size_type ix = 0; ix != 24; ++ix) {
        ivec.push_back(ix);
    }

    cout << "size - " << ivec.size()
         << "capacity - " << ivec.capacity() << endl;
    return 0;
}
