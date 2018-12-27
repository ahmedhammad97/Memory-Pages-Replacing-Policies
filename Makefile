output: main.o
	g++ main.o -o lab4

main.o: main.cc
	g++ -c main.cc
