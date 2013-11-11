#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include <boost/lexical_cast.hpp>

using namespace std;

int pivot(int l, int mid, int r){
	// choose the medium	
	if ((l < mid && mid <= r) || (r < mid && mid < l))
		return 1;
	else if ((mid < l && l < r) || (r < l && l <=mid))
		return 0;
	else if ((mid < r && r < l) || (l < r && r < mid))
		return 2;
}

int partition (vector <int> &A, int l, int r){
	int mid = floor((r+l)/2);
	int i = l+1;
	int tmp = 0;
	int p = 0;
	int x;
	
	x = pivot(A[l], A[mid], A[r]);
	
	switch (x){
		case 0: p = l;
			break;
		case 1: p = mid;
			break;
		case 2: p = r;
			break;
	}

	//preprocessing step
	if(p != l){
		tmp = A[p];
		A[p] = A[l];
		A[l] = tmp;
		p = l;	
	}
	
	for(int j = i; j <= r; ++j){
		if (A[j] < A[p]){
			tmp = A[j];
			A[j] = A[i];
			A[i] = tmp;
			++i;
		}
	}
	
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