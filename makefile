all: a.out

a.out: main.o square.o move.o state.o negamax.o utilities.o imcs.o player.o game.o
	g++ main.o square.o move.o state.o negamax.o utilities.o imcs.o player.o game.o

main.o: main.cpp
	g++ -c -g main.cpp

square.o: square.cpp square.h
	g++ -c -g square.cpp

move.o: move.cpp move.h
	g++ -c -g move.cpp

state.o: state.cpp state.h
	g++ -c -g state.cpp

negamax.o: negamax.cpp
	g++ -c -g negamax.cpp

utilities.o: utilities.cpp
	g++ -c -g utilities.cpp

imcs.o: imcs.cpp imcs.h
	g++ -c -g imcs.cpp

player.o: player.cpp player.h
	g++ -c -g player.cpp

game.o: game.cpp game.h
	g++ -c -g game.cpp
