// Trabalho Prático I - Grupo de Blackjack de Alunos da UFMG
// DCC206 - Algoritmos I - 2019/2 - UFMG
// Aluno: Caio Guedes de Azevedo Mota
// Professora: Jussara Marques

#ifndef GRAPH_TP1_ALG1
#define GRAPH_TP1_ALG1
#include <iostream>
#include <vector>
#include <list>
#include <climits>

// Grafo representando equipes de estudantes
// Contém métodos para trocar relações de comando, descobrir o comandante
// mais novo de algum aluno e gerar ordens de fala para reuniões
class Graph {
private:
	int _num_nodes;
	std::vector<int> _node_age;
	std::vector<std::list<int>> _node_adj;
public:
	Graph();

	// Métodos gerais de construção do grafo
	void AddNode(const int &age);
	void AddEdge(const int &i1, const int &i2);
	void PrintGraph();

	// Métodos para troca de relações de comando (SWAP)
	bool CheckCycle();
	bool DFSRecurCycle(const int &index, bool *visited, bool *recur);
	void Swap(const int &i1, const int &i2);
	bool SwapUtil(const int &i1, const int &i2);

	// Métodos para descobrir comandante mais novo (COMMANDER)
	void YoungestCommander(const int &target);
	void DFSRecurCommander(const int &index, const int &target,
			int youngest_current, int *youngest, bool *visited);

	// Métodos para gerar ordem de fala nas reuniões (MEETING)
	void Meeting();
	void DFSRecurMeeting(const int &index, bool *visited, std::vector<int> *stack);

};

#endif
