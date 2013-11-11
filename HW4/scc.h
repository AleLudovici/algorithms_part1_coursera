#ifndef SCC_H
#define SCC_H

#include <vector>
#include <iostream>

using namespace std;

class node {
	public:
		// constructor
		node(int label);
		// deconstructor
		~node();
		
		void set_explored();
		void set_unexplored();
		int check_explored();
		void add_edges(int edge);
		void print();
		void set_leader(int s);
		void set_time(int time);
				
		// the node name
		int name;
		// the outcoming edges 
		vector <int> edges;
		// marker
		int explored;
		// leader
		int leader;
		// finishing time
		int finish_time;
};

node::node(int label){
	name = label;
	explored = 0;
	leader = 0;
	finish_time = 0;
}

node::~node(){
	
}

void node::set_explored(){
	explored = 1;
}

void node::set_unexplored(){
	explored = 0;
}

int node::check_explored(){
	if (explored)
		return 1;
	else
		return 0;
}

void node::add_edges(int edge){
	edges.push_back(edge);	
}

void node::print(){
	cout << "node " << name << " is linked to" << endl;
	for(auto &i: edges)
		cout << " " << i << endl;
	cout << "leader is " << leader << endl;
	cout << "finish time is " << finish_time << endl;
}

void node::set_leader(int s){
	leader = s;
}

void node::set_time(int time){
	finish_time = time;
}
#endif