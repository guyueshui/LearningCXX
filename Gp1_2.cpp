/*
 * Search the insert pos for Insertion Sorting
 * write for group meeing homework h1p2
 * 2018年 11月 05日 星期一 22:58:06 CST
 */
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int fun(vector<int> vec, int val){
	if (val <= vec[0]) return 0;
	
	int i = 1;
	for (; i != vec.size(); ++i){
		if (val <= vec[i] && val > vec[i-1]) return i;
	}
	return i;
}

int main(int argc, char* argv[]){
	//argc = 3;
	//for (int i=0; i!=3; ++i){
	//	cout << argv[i] << endl;
	//}

	//vector<int> a;
	//string arr = argv[1];
	//cout << "arr is " << arr << endl;
	//for (auto i : arr){
	//	cout << i;
	//	a.push_back(int(i));
	//}
	//cout << "a[1] is " << a[1] << endl;
	//int b = 6;
	cout << "Input the sorted array and value " << endl;
	vector<int> a;
	int elem = 0;
	while (cin >> elem) {
		a.push_back(elem);
	}
	int b = *(a.end() - 1);
	a.pop_back();

	cout << "The array is: " << endl;
	for (auto i : a) cout << i << ' ';
	cout << endl << "The value is: " << b << endl;
	
	
	cout << "Now the index is: " << fun(a,b) << endl;
	
	return 0;
}
