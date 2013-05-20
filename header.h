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
const int MAX_DEPTH = 3;
const int MAX_SEC = 1;
const int MAX_TIME = MAX_SEC * CLOCKS_PER_SEC;

extern int g_max_depth;

void swap(int & x, int & y);
bool move_is_valid(string move);
void usage();

class Move;
class State;

int negamax(State current_state, int depth, Move & best_move);
int human_play(State & board, vector<Move> & themoves);
int bot_play(State & board, vector<Move> & themoves);
int human_turn(State & board, vector<Move> & themoves);
int bot_turn(State & board, vector<Move> & themoves);


#endif
