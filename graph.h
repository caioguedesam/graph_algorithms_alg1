#ifndef GRAPH_TP1_ALG1
#define GRAPH_TP1_ALG1
#include <iostream>
#include <vector>
#include <list>

class Graph {
private:
	int _num_nodes;
	std::vector<int> _node_age;
	std::vector<std::list<int>> _node_adj;
public:
	Graph();

	void AddNode(const int &age);
	void AddEdge(const int &i1, const int &i2);
	void PrintGraph();

	bool DFSCycle();
	bool DFSRecurCycle(const int &index, bool *visited, bool *recur);
	void Swap(const int &i1, const int &i2);
	bool SwapUtil(const int &i1, const int &i2);

	void YoungestCommander(const int &target);
	void DFSRecurCommander(const int &index, const int &target,
			int youngest_current, int *youngest, bool *visited);

};

#endif
