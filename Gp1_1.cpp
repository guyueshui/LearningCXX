/*
 * Merge two sorted sub seqs...
 * write for the group meeting homework: h1p1
 * 2018年 11月 05日 星期一 22:54:58 CST
 */
#include <iostream>
#include <vector>

using namespace std;

int main(){
	vector<int> a = {1, 2, 4};
	vector<int> b = {1, 3, 4};
	vector<int> c;

  int i,j;
	i = 0;
	j = 0;

	// compare & merge
	while (i != a.size() && j != b.size()){
		if (a[i] < b[j]){
			c.push_back(a[i]);
			++i;
		}else{
			c.push_back(b[j]);
			++j;
		}
	}

	// tail appending...
	if (i == a.size()){
		for (int iter = j; iter != b.size(); ++iter) c.push_back(b[iter]);
	}else{
		for (int iter = i; iter != a.size(); ++iter) c.push_back(a[iter]);
	}
	
	for (auto iter : c){
		cout << iter << ' ';
	}
	
	cout << "Merged!" << endl;
	return 0;
 }
