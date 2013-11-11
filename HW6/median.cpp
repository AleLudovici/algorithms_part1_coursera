/*The goal of this problem is to implement the "Median Maintenance" algorithm (covered in the Week 5 lecture on heap applications). 
The text file contains a list of the integers from 1 to 10000 in unsorted order; 
you should treat this as a stream of numbers, arriving one by one. 
Letting xi denote the ith number of the file, the kth median mk is defined as the median of the numbers x1,…,xk. 
(So, if k is odd, then mk is ((k+1)/2)th smallest number among x1,…,xk; if k is even, then mk is the (k/2)th smallest number among x1,…,xk.)
In the box below you should type the sum of these 10000 medians, modulo 10000 (i.e., only the last 4 digits). 
That is, you should compute (m1+m2+m3+⋯+m10000)mod10000.

TEST CASE is 8046
*/

#include <fstream>
#include <string>
#include <map>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

map <int, int> G;
vector <int> M;
int k = 0;

void median (){
	int element;
	map <int, int>::iterator it;
	
	
	k++;
	
	if (k % 2) {
	/* x is odd */ 
		element = (k+1)/2;
	} else {
	/* x is even */
		element = k/2;
	}
	
	it = G.begin();
	
	for(int i = 1 ; i <= element - 1; i++)	
		++it;
	
	M.push_back(it->first); 
	
	return;
}



int main(){
	ifstream myfile ("Median.txt");
	string line;	
	int num, sum = 0, med = 0;
	
	if (myfile.is_open()){
		while(!myfile.eof()){
			getline(myfile,line);			
			num = stoi( line );	
			G.insert({num, 0});
			median();
		}
		myfile.close();
	} else {
		cout << "Unable to open file" << endl;
	}		
    
	for (int i = 0; i < 30; i++)
		cout << "median is " << M[i] << endl;
	
	for(auto &p: M)
		sum += p;
	
	med = sum % 10000;
	
	cout << "median is: " << med << endl;
		
	return 0;
}