#include "graph.h"
#include <string>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[]) {

	auto file = std::ifstream(std::string(argv[1]));	
	
	std::string line;

	int num_alunos, num_comandos, num_instrucoes;
	std::getline(file, line);
	auto line_stream = std::stringstream(line);

	line_stream >> num_alunos >> num_comandos >> num_instrucoes;

	Graph *g = new Graph();

	std::getline(file, line);
	line_stream = std::stringstream(line);

	int i;
	for(i = 0; i < num_alunos; i++) {
		int age;
		line_stream >> age;
		g->AddNode(age);
	}

	for(i = 0; i < num_comandos; i++) {
		std::getline(file, line);
		line_stream = std::stringstream(line);

		int i1, i2;
		line_stream >> i1 >> i2;
		g->AddEdge(i1-1, i2-1);
	}

	for(i = 0; i < num_instrucoes; i++) {
		std::getline(file, line);
		line_stream = std::stringstream(line);

		char instr;
		line_stream >> instr;
		if(instr == 'S') {
			int i1, i2;
			line_stream >> i1 >> i2;
			g->Swap(i1-1, i2-1);
		}
		else if(instr == 'C') {
			int target;
			line_stream >> target;
			g->YoungestCommander(target-1);
		}
		else if(instr == 'M')
			g->Meeting();
	}

	file.close();
	delete g;
	return 0;
}
