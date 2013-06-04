all: a.out

a.out: .main.o .square.o .move.o .state.o .negamax.o .utilities.o .imcs.o .player.o .game.o .piece.o .zobrist.o .ttable.o .ttable_entry.o header.h
	g++ .main.o .square.o .move.o .state.o .negamax.o .utilities.o .imcs.o .player.o .game.o .piece.o .zobrist.o .ttable.o .ttable_entry.o

.main.o: main.cpp header.h
	g++ -c -g main.cpp -o .main.o

.square.o: square.cpp square.h header.h
	g++ -c -g square.cpp -o .square.o

.move.o: move.cpp move.h header.h
	g++ -c -g move.cpp -o .move.o

.state.o: state.cpp state.h header.h
	g++ -c -g state.cpp -o .state.o

.negamax.o: negamax.cpp header.h
	g++ -c -g negamax.cpp -o .negamax.o

.utilities.o: utilities.cpp header.h
	g++ -c -g utilities.cpp -o .utilities.o

.imcs.o: imcs.cpp imcs.h header.h
	g++ -c -g imcs.cpp -o .imcs.o

.player.o: player.cpp player.h header.h
	g++ -c -g player.cpp -o .player.o

.game.o: game.cpp game.h header.h
	g++ -c -g game.cpp -o .game.o

.piece.o: piece.cpp piece.h header.h
	g++ -c -g piece.cpp -o .piece.o

.zobrist.o: zobrist.cpp zobrist.h
	g++ -c -g zobrist.cpp -o .zobrist.o

.ttable.o: ttable.cpp ttable.h
	g++ -c -g ttable.cpp -o .ttable.o

.ttable_entry.o: ttable_entry.cpp ttable_entry.h
	g++ -c -g ttable_entry.cpp -o .ttable_entry.o

clean:
	rm *.o a.out
