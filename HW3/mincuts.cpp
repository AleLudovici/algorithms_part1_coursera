#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <boost/lexical_cast.hpp>
#include <stdio.h>
#include <stdlib.h>

/*
 * Randomized contraction algorithm for the min cut problem. 
 * Compute the min cut of the grapg given in the file
 */

using namespace std;
using namespace boost;


int count_cut (map <int, vector<int>>& H){
	int n_index, m_index, index = 1, edge_rdm;
	map <int, vector<int>> CG;
	map <int, vector<int>>::iterator it, nt, map;
	
	
	CG.insert(H.begin(), H.end());
			
	while (CG.size() > 2){
		// randomly choose an edge
		index = 0;
		do{
			n_index = 1 + (rand() % H.size());
		}while ((it = CG.find(n_index)) == CG.end());							

				
		do {
			edge_rdm = (rand() % it->second.size());			
			m_index = it->second.at(edge_rdm);
			if (index > 100)
				break;
			index++;
		}while((nt = CG.find(m_index)) == CG.end());
		
	if(index < 100){
		
		// contract graph
		it->second.insert(it->second.end(), nt->second.begin(), nt->second.end());
		
		// remove loops
		for (int i = 0; i < it->second.size(); i++){
			if((it->second.at(i) == nt->first) || (it->second.at(i) == it->first))
				it->second.erase(it->second.begin() + i);			
		}

		
		for(map = CG.begin(); map != CG.end(); map++){
			if((map->first != it->first) || (map->first != nt->first))
				for(int x = 0; x < map->second.size(); x++)
					if (map->second.at(x) == nt->first)
						map->second.at(x) = it->first; 
					}

		CG.erase(nt);				
	 } else {
		for(map = CG.begin(); map != CG.end(); map++){
			if((map->first != it->first)){
				for(int x = 0; x < map->second.size(); x++)
					if (map->second.at(x) == it->first)
						map->second.erase(map->second.begin() + x);
			} 
		}
		CG.erase(it);
	}		
	}
	it = CG.begin();
	nt = it++;
	
	cout << it->first << " : ";
	for (auto &p: it->second)
		cout << p << " ";
	cout << endl;
	
	cout << nt->first << " : ";
	for (auto &z: nt->second)
		cout << z << " ";
	cout << endl;
	
    it->second.erase(std::remove(it->second.begin(), it->second.end(), it->first), it->second.end());
    nt->second.erase(std::remove(nt->second.begin(), nt->second.end(), nt->first), nt->second.end());

	
	for (int j = 0; j < nt->second.size(); j++){
		cout << "[" << j << "] " <<  nt->second.at(j) << " " << nt->first << endl;
		if(nt->second.at(j) == nt->first)
			nt->second.erase(nt->second.begin() + j);			
	}
	cout << "no loops " << endl;
	cout << it->first << " : ";
	for (auto &p: it->second)
		cout << p << " ";
	cout << endl;
	
	cout << nt->first << " : ";
	for (auto &z: nt->second)
		cout << z << " ";
	cout << endl;
	
	 if (it->second.size() <= nt->second.size()) 
		return it->second.size();
	else
		return nt->second.size();
}

int main(){
	ifstream myfile ("kargerMinCut.txt");
	map <int, vector<int>> G;
	map <int, vector<int>>::iterator it;
	vector <int> E, cut;
	vector <string> A;
	string line, buf;	
	int num, node, i = 1, mincut, min;
	
	if (myfile.is_open()){
		while(!myfile.eof()){
			getline(myfile,line);			
			stringstream ss(line);
			while (ss >> buf)
				A.push_back(buf);	
			
			for(int i = 0; i < size(A); i++){
				num = stoi(A[i]);
				if(!i)
					node = num;
				else
					E.push_back(num);	
			}
			G.insert({node, E});
			A.clear();
			E.clear();
		}
		myfile.close();
	} else {
		cout << "Unable to open file" << endl;
	}		
			
	
	while (i <= 100){
		mincut = count_cut(G);		
		if (i==1)
			min = mincut;			
		if (mincut < min)
			min = mincut;
		cout << "[" << i << "] = " << min << endl;
		++i;
	}

	cout << "min_cut is: " << min << endl;
		
	return 0;
}