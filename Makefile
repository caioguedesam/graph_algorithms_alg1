tp1: main.o graph.o
	g++ main.o graph.o -o tp1
	make clean

main.o: main.cpp
	g++ -c main.cpp

graph: graph.cpp graph.h
	g++ -c graph.cpp

clean:
	rm *.o
