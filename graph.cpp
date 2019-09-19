#include "graph.h"

Graph::Graph() {
	_num_nodes = 0;
}

void Graph::AddNode(const int &age) {
	_node_age.push_back(age);
	std::list<int> neighbors;
	_node_adj.push_back(neighbors);
	_num_nodes++;
}

void Graph::AddEdge(const int &i1, const int &i2) {
	std::list<int>::iterator it;
	for(it = _node_adj[i1].begin(); it != _node_adj[i1].end(); it++) {
		if(*it == i2)
			return;
	}
	_node_adj[i1].push_back(i2);
}	

void Graph::PrintGraph() {
	std::list<int>::iterator it;
	int i;
	for(i = 0; i < _num_nodes; i++) {
		std::cout << i+1 << " - Age: " << _node_age[i] << std::endl;
		for(it = _node_adj[i].begin(); it != _node_adj[i].end(); it++) {
			std::cout << "(" << *it+1 << ") -> ";
		}
		std::cout << "X" << std::endl;
	}
}

bool Graph::DFSCycle() {
	bool visited[_num_nodes];
	bool recur[_num_nodes];
	int i;
	for(i = 0; i < _num_nodes; i++) {
		recur[i] = false;
		visited[i] = false;
	}

	for(i = 0; i < _num_nodes; i++)
		if(DFSRecurCycle(i, visited, recur))
			return true;
	return false;
}

bool Graph::DFSRecurCycle(const int &index, bool *visited, bool *recur) {
	if(visited[index] == false) {
		recur[index] = true;
		visited[index] = true;
		for(auto it = _node_adj[index].begin(); it != _node_adj[index].end(); it++) {
			if(!visited[*it] && DFSRecurCycle(*it, visited, recur))
				return true;
			else if (recur[*it])
				return true;
		}
	}
	recur[index] = false;
	return false;
}

bool Graph::SwapUtil(const int &i1, const int &i2) {
	for(auto it = _node_adj[i1].begin(); it != _node_adj[i1].end(); it++) {
		if(*it == i2) {
			_node_adj[i1].erase(it);
			this->AddEdge(i2, i1);
			if(this->DFSCycle()) {
				_node_adj[i2].pop_back();
				this->AddEdge(i1, i2);
				return false;
			}
			return true;
		}
	}
	return false;
}

void Graph::Swap(const int &i1, const int &i2) {
	if(this->SwapUtil(i1,i2))
		std::cout << "S T" << std::endl;
	else if(this->SwapUtil(i2,i1))
		std::cout << "S T" << std::endl;
	else
		std::cout << "S N" << std::endl;
}
