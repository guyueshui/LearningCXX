// 探究vector容量的增长方式
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
    std::vector<int> ivec;
    for (vector<int>::size_type ix = 0;
         ix != 100; ++ix)
    {
        ivec.push_back(ix);
        if (ivec.size() == ivec.capacity())
                cout << ivec.capacity() << ' ';
    }
    return 0;
}

// std::cout is
// 1 2 4 8 16 32 64
