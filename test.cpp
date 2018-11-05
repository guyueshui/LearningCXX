#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
	vector<int> arr = {1,2,3,4,5,6,7,8,9};
	int len = arr.size();
	int lsize = len >> 1;
	int rsize = len - lsize;
	
	vector<int> larr, rarr;
	larr.assign(arr.begin(), arr.begin()+lsize);
	rarr.assign(arr.end()-rsize, arr.end());
	
	for (auto i : larr) std::cout << i << '\n';
	std::cout << "-----------\n";
	for (auto i : rarr) std::cout << i << '\n';
	return 0;
}
