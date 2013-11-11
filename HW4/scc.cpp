#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <boost/lexical_cast.hpp>
#include "scc.h"
#include "quicksort.h"

/*
* Copute the strongly connected components (SCCs) of a directed graph.
*/
using namespace std;
using namespace boost;

int t = 0;
int s = 0;
int pass = 0;

void dfs (map <int, node>& H, int i){
	map <int, node>::iterator it, et;
	
	// mark i as explored
	it = H.find(i);
	it->second.set_explored();	
	
	// set leader (only 2nd pass)
	if (pass == 2)
		it->second.set_leader(s);

	// recursive call DFS on each arcs
	for (auto &p: it->second.edges){
		// if edge node not explored call dfs
		if (p != 0){
			et = H.find(p);
			if(!et->second.check_explored())
			dfs(H, et->first);
		} 
	}
	
	// set finishing_time (only 1st pass)
	if (pass == 1){
		t++;
		it->second.set_time(t);	
	}
	
	return;
}

map <int, int> dfs_loop (map <int, node>& H, map <int, int>& V){
	map <int, node>::iterator it;
	map <int, int> ret;
	map <int, int>::iterator st;
	int i;
			
	// first pass
	if(pass == 1){
		for (int j = H.size(); j >= 1; j--){
			// select nodes in revers order
			it = H.find(j);		
			// check if not yet explored
			if (!it->second.check_explored()){
				s = it->first;
				dfs(H, it->first);	
			}
		}
		
		// create map of nodes following the finishing time
		for (auto &i: H)
			ret.insert({i.second.finish_time, i.second.name});
		
		return ret;	
	}
	
	
	for (int j = V.size(); j >= 1; j--){
		// select nodes in revers order
		st = V.find(j);	
		it = H.find(st->second);	
		// check if not yet explored
		if (!it->second.check_explored()){
			s = it->first;
			dfs(H, it->first);	
		}
	}	
						
	// a SCC is formed by nodes sharing the same leaders
	// create an entry in map scc_size for each leader
	for(auto &p: H)
		if ((st = ret.find(p.second.leader)) == ret.end())
			ret.insert({p.second.leader, 1});
		else
			st->second++;
		
	return ret;
}

int main(){
	ifstream myfile ("SCC.txt");
	map <int, node> G, R;
	map <int, node>::iterator it, rit;
	map <int, int> scc_size, time_order;
	vector <string> A;
	vector <int> SZ;
	vector<int>::iterator cit;
	string line, buf;	
	int num, tail, head;
	
	if (myfile.is_open()){
		while(!myfile.eof()){
			getline(myfile,line);			
			stringstream ss(line);
			while (ss >> buf)
				A.push_back(buf);
				if(A.size() == 1)
					cout << "no head" << endl;				
			for(int i = 0; i < size(A); i++){
				num = stoi(A[i]);
				if(!i)
					tail = num;
				else
					head = num;
			}
			// Create Graph
			if ((it = G.find(tail)) == G.end()){
				//create object node
				node new_node(tail);
				//add edges
				new_node.add_edges(head);
				G.insert({tail, new_node});
			} else {
				// insert only the edge to the existing node
				it->second.add_edges(head);
			}
			
			// Create Reverse Graph
			if((rit = R.find(head)) == R.end()){
				node new_rev_node(head);
				new_rev_node.add_edges(tail);
				R.insert({head, new_rev_node});
			} else {
				rit->second.add_edges(tail);
			}
			A.clear();
		}
		myfile.close();
	} else {
		cout << "Unable to open file" << endl;
	}
	
	for (int x = 1; x <= 875714; x++){
		 if((it = G.find(x)) == G.end()){
			//create object node
			node new_node(x);
			//add edges
			new_node.add_edges(0);
			G.insert({x, new_node});
		}
		 if((rit = R.find(x)) == R.end()){
			//create object node
			node new_rev_node(x);
			//add edges
			new_rev_node.add_edges(0);
			R.insert({x, new_rev_node});
		}
	}	
	
	pass = 1;
	time_order = dfs_loop(R, time_order);	
	cout << "time done" << endl;
	pass = 2;
	scc_size = dfs_loop(G, time_order);
	cout << "scc done" << endl;
	
	for (auto &c: scc_size)
		if(c.second > 100)
			SZ.push_back(c.second);
		
	// use quick_sort SCC to get the five larget SCC
	quick_sort(SZ, 0, static_cast<int>(SZ.size()) -1 );
	cout << SZ.size() << endl;
	
	cit = SZ.end();
	
	for (int i = 1; i <=5; i++){
		cit--;
		cout << "size of scc is: " << *cit << endl;			
	}		
	return 0;
}