all: a.out

a.out: main.o square.o move.o state.o negamax.o utilities.o
	g++ main.o square.o move.o state.o negamax.o utilities.o

main.o: main.cpp
	g++ -c -g main.cpp

square.o: square.cpp
	g++ -c -g square.cpp

move.o: move.cpp
	g++ -c -g move.cpp

state.o: state.cpp
	g++ -c -g state.cpp

negamax.o: negamax.cpp
	g++ -c -g negamax.cpp

utilities.o: utilities.cpp
	g++ -c -g utilities.cpp
