#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <boost/lexical_cast.hpp>

/*
 * This program computes the number of inversions in the file given, 
 * where the ith row of the file indicates the ith entry of an array.
 * 
 * This program implements the divide-and-conquer algorithm.
 */

using namespace std;
unsigned int inv = 0;

void merge(vector <int> &A, int l, int r){
	int mid = (r+l)/2;
	int i1 = 0;
	int i2 = l;
	int i3 = mid+1;
	
	cout << "(" << l << "," << r << ") = ";
	for(int x = l; x <= r; x++)
		cout << A[x] << " ";
	cout << endl;	
	
	vector<int> tmp;
	tmp.reserve(r-l+1);
	
	while(i2 <= mid && i3 <= r){
		if(A[i2] < A[i3])
			tmp[i1++] = A[i2++];
		else{
			if(r-l > 1)
				inv += mid-i2+1;
			else
				inv++;
			tmp[i1++] = A[i3++];	
		}			
	}
	
	while (i2 <= mid)
		tmp[i1++] = A[i2++];
		
	while (i3 <= r)
		tmp[i1++] = A[i3++];
		
	for(int i = l; i <= r; i++)
		A[i] = tmp[i-l];
		
	return;
}

void merge_sort (vector <int> &A, int l, int r){
	if(l < r){
		int mid = (r+l)/2; 
		merge_sort(A, l, mid);
		merge_sort(A, mid+1, r);
		merge(A, l, r);
	}	
	return;
}

int main(){
	ifstream myfile ("IntegerArray.txt");
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
	
	merge_sort(A, 0, A.size()-1);
	
	cout << "sorted: " << endl;
	for(auto &i: A)
		cout << i << " ";
	cout << endl;
	
	cout << "inversion are: " << inv << endl;
		
	return 0;
}