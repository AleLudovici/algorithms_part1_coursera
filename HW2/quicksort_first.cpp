#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <boost/lexical_cast.hpp>

/* 
 * Compute the total number of comparisons used to sort the given input file by QuickSort.
 * This version of QuickSort uses the first element of the array as the pivot
 */
using namespace std;
unsigned int cmp = 0;

int partition (vector <int> &A, int l, int r){
	int p = l;
	int i = l+1;
	int tmp = 0;
	
	for(int j = i; j <= r; ++j){
		if (A[j] < A[p]){
			tmp = A[j];
			A[j] = A[i];
			A[i] = tmp;
			++i;
		}			
	}
	cmp += (r - l);
	
	tmp = A[p];
	A[p] = A[i-1];
	A[i-1] = tmp;
	
	return i-1;
}


void quick_sort (vector <int> &A, int l, int r){
	int p;
	
	if (l < r ){
		p = partition(A, l, r);	
		quick_sort(A, l, p-1);
		quick_sort(A, p+1, r);		
	}	

	return;
}


int main(){
	ifstream myfile ("Test.txt");
	vector <int> A;
	vector <string> S;
	string line;	
	int num;
	
	if (myfile.is_open()){
		while(!myfile.eof()){
			getline(myfile,line);
			num = stoi( line );
			A.push_back(num);
		}
		myfile.close();
	} else {
		cout << "Unable to open file" << endl;
	}		

	
	quick_sort(A, 0, A.size()-1);
	
	cout << "sorted: " << endl;
	for(auto &i: A)
		cout << i << " ";
	cout << endl;
	
	cout << "comparisons are: " << cmp << endl;
		
	return 0;
}