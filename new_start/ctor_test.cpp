#include <iostream>

using std::cout;


struct Vector3
{
    /*
    Vector3(): x(0), y(0), z(0)
    { cout << "default ctor called\n"; }
    */
    // Vector3()=default;

    Vector3(const Vector3& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        cout << "copy ctor called\n";
    }


    Vector3& operator=(const Vector3& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        cout << "copy assignment called\n";
        return *this;
    }

    Vector3(Vector3&&) = delete;
    Vector3& operator=(Vector3&&) = delete;
    ~Vector3() = default;

    Vector3(const float& x, const float& y, const float& z)
        : x(x), y(y), z(z)
    { cout << "specific ctor called\n"; }

    float x, y, z;
};


struct A
{
    Vector3 vec1;
    Vector3 vec2 {1, 2, 3};
    // Vector3 vec3 (4, 5, 6);
    Vector3 vec4 = Vector3(7, 8, 9);
    Vector3 vec5 = {10, 11, 12};
};


int main()
{
    // A a;
    return 0;
    // Vector3 v1;                     // default ctor
    Vector3 v2(1, 2, 3);            // specific ctor
    Vector3 v3 = Vector3(4,5,6);    // same as above
    Vector3 v4 = v3;                // copy ctor
    Vector3 v5(v4);                 // same as above
    v2 = v5;                        // copy assignment
    return 0;
}
