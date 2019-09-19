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

void Graph::YoungestCommander(const int &index) {
	bool visited[_num_nodes];
	int i;
	for(i = 0; i < _num_nodes; i++)
		visited[i] = false;

	int youngest = 999;

	for(i = 0; i < _num_nodes; i++) {
		DFSRecurCommander(i, index, _node_age[i], &youngest, visited);
	}

	if(youngest == 999)
		std::cout << "C *" << std::endl;
	else
		std::cout << "C " << youngest << std::endl;
}

void Graph::DFSRecurCommander(const int &index, const int &target,
		int youngest_current, int *youngest, bool *visited) {
	if(!visited[index]) {
		visited[index] = true;
		if(_node_age[index] < youngest_current)
			youngest_current = _node_age[index];

		for(auto it = _node_adj[index].begin(); it != _node_adj[index].end(); it++) {
			if(*it == target && youngest_current < *youngest)
				*youngest = youngest_current;
			else if(!visited[*it])
				DFSRecurCommander(*it, target, youngest_current, youngest, visited);
		}
	}
}
