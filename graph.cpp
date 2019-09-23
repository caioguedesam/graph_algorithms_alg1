#include "graph.h"

Graph::Graph() {
	_num_nodes = 0;
}

// AddNode: Adiciona um vértice ao grafo, representando um
// novo aluno na equipe
//
// @params
// age: idade do aluno novo
void Graph::AddNode(const int &age) {
	_node_age.push_back(age);
	std::list<int> neighbors;
	_node_adj.push_back(neighbors);
	_num_nodes++;
}

// AddEdge: Adiciona uma aresta ao grafo, representando uma
// relação de comando entre dois alunos
//
// @params
// i1: posição no grafo do aluno comandante
// i2: posição no grafo do aluno comandado
void Graph::AddEdge(const int &i1, const int &i2) {
	std::list<int>::iterator it;
	for(it = _node_adj[i1].begin(); it != _node_adj[i1].end(); it++) {
		if(*it == i2)
			return;
	}
	_node_adj[i1].push_back(i2);
}	

// PrintGraph: Imprime todos os vértices e seus vizinhos no grafo.
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

// CheckCycle: Percorre o grafo procurando algum ciclo.
//
// @return: 
// true se o grafo contém ciclo
// false se não contém
bool Graph::CheckCycle() {
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

// DFSRecurCycle: Caminha o grafo usando DFS recursiva, chamada por CheckCycle.
//
// @params
// index: índice do vértice visitado pela chamada recursiva atual
// visited: vetor armazenando vértices já visitados
// recur: vetor armazenando vértices ainda não totalmente explorados
//
// @return:
// true se acha um ciclo na chamada recursiva
// false caso contrário
bool Graph::DFSRecurCycle(const int &index, bool *visited, bool *recur) {
	if(visited[index] == false) {
		recur[index] = true;
		visited[index] = true;
		// Explorar os vizinhos do vértice. Caso ache um vértice que ainda não foi
		// terminado durante a busca, retorna verdadeiro.
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

// Swap: Troca as arestas entre dos vértices. Caso não haja aresta indo de
// um vértice i1 até um vértice i2, procura uma de i2 a i1 e tenta trocar.
// Caso contrário, não troca nada.
// Usa da função SwapUtil para de fato fazer as trocas.
//
// @params
// i1, i2: posições no grafo dos vértices a trocar a aresta.
void Graph::Swap(const int &i1, const int &i2) {
	if(this->SwapUtil(i1,i2))
		std::cout << "S T" << std::endl;
	else if(this->SwapUtil(i2,i1))
		std::cout << "S T" << std::endl;
	else
		std::cout << "S N" << std::endl;
}

// SwapUtil: Faz efetivamente a troca da aresta entre vértices.
// Se i2 é vizinho de i1, troca a aresta. Caso a troca resulte em ciclo,
// reverte a troca.
//
// @params
// i1, i2: posições no grafo dos vértices a trocar a aresta
// @return:
// true se a troca foi feita
// false se a troca ocasionou ciclo e foi revertida
bool Graph::SwapUtil(const int &i1, const int &i2) {
	for(auto it = _node_adj[i1].begin(); it != _node_adj[i1].end(); it++) {
		if(*it == i2) {
			_node_adj[i1].erase(it);
			this->AddEdge(i2, i1);
			if(this->CheckCycle()) {
				_node_adj[i2].pop_back();
				this->AddEdge(i1, i2);
				return false;
			}
			return true;
		}
	}
	return false;
}

// YoungestCommander: Procura o comandante mais novo de um dado vértice
// do grafo. Usa uma variável auxiliar que, caso continue igual após
// a execução, significa que o vértice não tem arestas entrando nele.
//
// @params
// index: posição do vértice a descobrir o mais novo que o comanda
void Graph::YoungestCommander(const int &index) {
	bool visited[_num_nodes];
	int i;
	for(i = 0; i < _num_nodes; i++)
		visited[i] = false;

	int youngest = INT_MAX;

	// Faz uma DFS em todo o grafo 
	for(i = 0; i < _num_nodes; i++) {
		DFSRecurCommander(i, index, _node_age[i], &youngest, visited);
	}

	if(youngest == INT_MAX)
		std::cout << "C *" << std::endl;
	else
		std::cout << "C " << youngest << std::endl;
}

// DFSRecurCommander: Faz DFS para procurar o mais novo, usado pela função
// acima. Guarda um mais novo da busca e o mais novo no geral. Vai progres-
// sivamente armazenando o mais novo na busca e, se achar o vértice deseja-
// do, atualiza o mais novo geral como sendo o mais novo da busca.
//
// @params
// index: vértice atual sendo analisado
// target: vértice a descobrir o comandante mais novo
// youngest_current: idade mais nova da dada busca
// youngest: idade mais nova encontrada que comanda target
// visited: vetor que guarda vértices que já foram visitados
void Graph::DFSRecurCommander(const int &index, const int &target,
		int youngest_current, int *youngest, bool *visited) {
	if(!visited[index]) {
		visited[index] = true;
		// Caso o vértice atual seja mais novo que a idade mais nova da busca,
		// atualiza o valor do mais novo
		if(_node_age[index] < youngest_current)
			youngest_current = _node_age[index];

		for(auto it = _node_adj[index].begin(); it != _node_adj[index].end(); it++) {
			// Se encontrar o vértice desejado, quer dizer que esse mais novo atual
			// é um comandante desse vértice. Atualizar o comandante mais novo
			if(*it == target && youngest_current < *youngest)
				*youngest = youngest_current;
			else if(!visited[*it])
				DFSRecurCommander(*it, target, youngest_current, youngest, visited);
		}
	}
}

// Meeting: Imprime uma ordem topológica dos vértices do grafo. Guarda
// uma pilha com a ordem topológica e a imprime.
void Graph::Meeting() {
	std::vector<int> stack;
	bool visited[_num_nodes];

	int i;
	for(i = 0; i < _num_nodes; i++)
		visited[i] = false;

	for(i = 0; i < _num_nodes; i++)
		DFSRecurMeeting(i, visited, &stack);

	for(auto it = stack.rbegin(); it != stack.rend(); it++)
		std::cout << *it+1 << " ";
	std::cout << std::endl;
}

// DFSRecurMeeting: Faz um DFS guardando vértices totalmente explorados em uma pilha
// assim que terminam de ser explorados. Usado pela função acima.
//
// @params
// index: vértice atual
// visited: vetor de vértices já visitados
// stack: pilha de vértices já totalmente explorados
void Graph::DFSRecurMeeting(const int &index, bool *visited, std::vector<int> *stack) {
	if(!visited[index]) {
		visited[index] = true;
		for(auto it = _node_adj[index].begin(); it != _node_adj[index].end(); it++)
			DFSRecurMeeting(*it, visited, stack);
		stack->push_back(index);
	}
}
		
