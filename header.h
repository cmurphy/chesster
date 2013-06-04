#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#ifdef DEBUG
#undef DEBUG
#endif
//#define DEBUG

const bool white = true;
const bool black = false;
const int MAX_MOVES = 40;
//const int MAX_DEPTH = 3;
const int MAX_SEC = 1;
const int MAX_TIME = MAX_SEC * CLOCKS_PER_SEC;
const int MAX_SCORE = 9600;

/* Piece values */
const int PAWN_VAL = 100;
const int BISHOP_VAL = 300;
const int KNIGHT_VAL = BISHOP_VAL;
const int ROOK_VAL = 500;
const int QUEEN_VAL = 1000;
const int KING_VAL = 5000;

extern int g_max_depth;

void swap(int & x, int & y);
bool move_is_valid(const string move);
void usage();
int piece_value(char piece);
int piece_index(char piece);

class Move;
class State;

int negamax(State current_state, int depth, clock_t start_time, int & states_evaluated, int alpha, int beta);
int human_play(State & board, vector<Move> & themoves);
int bot_play(State & board, vector<Move> & themoves);
int human_turn(State & board, vector<Move> & themoves);
int bot_turn(State & board, vector<Move> & themoves);


#endif
