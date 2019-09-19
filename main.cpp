#include "graph.h"

int main() {

	int num_alunos, num_comandos, num_instrucoes;
	std::cin >> num_alunos >> num_comandos >> num_instrucoes;

	Graph *g = new Graph();

	int i;
	for(i = 0; i < num_alunos; i++) {
		int age;
		std::cin >> age;
		g->AddNode(age);
	}

	for(i = 0; i < num_comandos; i++) {
		int i1, i2;
		std::cin >> i1 >> i2;
		g->AddEdge(i1-1, i2-1);
	}

	for(i = 0; i < num_instrucoes; i++) {
		char instr;
		std::cin >> instr;
		if(instr == 'S') {
			int i1, i2;
			std::cin >> i1 >> i2;
			g->Swap(i1-1, i2-1);
		}
		else if(instr == 'C') {
			int target;
			std::cin >> target;
			g->YoungestCommander(target-1);
		}
		else if(instr == 'M')
			g->Meeting();
	}

	delete g;
	return 0;
}
