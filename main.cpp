// Trabalho Prático I - Grupo de Blackjack de Alunos da UFMG
// DCC206 - Algoritmos I - 2019/2 - UFMG
// Aluno: Caio Guedes de Azevedo Mota
// Professora: Jussara Marques

#include "graph.h"
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std::chrono;

int main(int argc, char *argv[]) {

	// Estabelecendo início do tempo de execução
	auto start_clock = high_resolution_clock::now();

	// Lendo arquivo pela linha de comando
	auto file = std::ifstream(std::string(argv[1]));	
	std::string line;

	// Lendo linha do arquivo e criando um stream para obter
	// informações da linha
	std::getline(file, line);
	auto line_stream = std::stringstream(line);

	int num_alunos, num_comandos, num_instrucoes;
	line_stream >> num_alunos >> num_comandos >> num_instrucoes;

	// Criando grafo e o populando
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

	// Terminando o tempo de execução e calculando em nanossegundos
	auto end_clock = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end_clock - start_clock);
	int time = int(duration.count());

	
	// Fechando o arquivo de entrada
	file.close();
	delete g;
	return 0;
}
