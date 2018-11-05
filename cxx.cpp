#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
	string foo = "I am foo";
	string bar("I am bar");

	string& fooRef = foo;
	// string& const c1fooRef = foo;			
	// invalid, 不存在常引用，引用本身不是一个对象
	// 不能用 const 修饰
	const string& c2fooRef = foo;
	// 对常量的引用，可以将对常量的引用绑定到非常量对象
	cout << fooRef << endl
			 //	<< c1fooRef << endl
			 << c2fooRef << endl;
	return 0;
}

