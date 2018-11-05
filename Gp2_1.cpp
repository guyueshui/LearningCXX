#include <iostream>
#include <vector>

using namespace std;

// 声明静态全局变量，只初始化一次
static int INVCOUNT = 0;

// combine two sorted subseqs
vector<int> merge(vector<int>& a, vector<int>& b){
	vector<int> res; // result seq
	vector<int>::iterator i = a.begin();
	vector<int>::iterator j = b.begin();
	while(i != a.end() && j != b.end()){
		if (*i <= *j) res.push_back(*(i++));
		if (*i > *j){
			res.push_back(*(j++));
			INVCOUNT += (a.end() - i);
		}
	}
	
	// tail appending ...
	if (i == a.end()){
		for(auto iter = j; iter != b.end(); ++iter) res.push_back(*iter);
	}
	if (j == b.end()){
		for(auto iter = i; iter != a.end(); ++iter) res.push_back(*iter);
	}

	return res;
}

// 归并排序的递归形式
vector<int> mergesort(vector<int>& seq){
	if (seq.size() == 1) return seq;
	else{
		int lsize = seq.size() >> 1;
		int rsize = seq.size() - lsize;
		vector<int> tmpl, tmpr, lseq, rseq;
		tmpl.assign(seq.begin(), seq.begin()+lsize);
		tmpr.assign(seq.end()-rsize, seq.end());
		lseq = mergesort(tmpl);
		rseq = mergesort(tmpr);

		return merge(lseq, rseq);
	}
}

int main(){
	vector<int> vec = {6,5,4,3,2,1};
	vector<int> result = mergesort(vec);
	for(auto i:result){cout << i << '\n';}
	cout << "The # of inversion pairs is " << INVCOUNT << endl;
	return 0;
}
