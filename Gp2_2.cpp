/*
 * A implemention for quick sort
 * write for group meeting homework h2p2
 * 2018年 11月 05日 星期一 22:59:16 CST
 */
#include <iostream>
#include <vector>

using namespace std;

void swap(int& a, int& b){
	int tmp = a;
	a = b;
	b = tmp;
}

int partition(vector<int>& A, int p, int r){
	int pivot = A[p-1];
	int i = p;
	for (int j=p; j!=r; ++j){
		if (A[j] < pivot){
			// exchange A[storeIdx] with A[i]
			swap(A[i], A[j]);
			++i;
		}
	}

	// exchange the index of pivot with A[i - 1]
	swap(A[p-1], A[i-1]);
	return i;
}

void quick_sort(vector<int>& A, int p, int r){
	if (p < r){
		int q = partition(A, p, r);
		quick_sort(A, p, q-1);
		quick_sort(A, q+1, r);
	}
}

int main(){
	vector<int> seq = {2,4,6,9,0,5,7,3,5,7,1,2,3,9,5,8,4,7,6,2};
	quick_sort(seq, 1, seq.size());
	for (auto i:seq) cout << i <<	'\n';
	return 0;
}
