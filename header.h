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
const int BOARD_SIZE_X = 5;
const int BOARD_SIZE_Y = 6;
const int MAX_DEPTH = 3;
const int MAX_TIME = 10000;

extern int g_max_depth;

void swap(int & x, int & y);
bool move_is_valid(string move);

class Square
{
  public:
    Square();
    Square(int x, int y);
    void print();
    char * to_s();
    bool operator==(const Square & othersquare);
    friend ostream & operator<<(ostream & out, const Square & asquare);
    void getxy(int & x, int & y);
  private:
    int x;
    int y;
};

class Move
{
  private:
    Square to_Square;
    Square from_Square;
  public:
    Move();
    Move(int x0, int y0, int xn, int yn);
    Move(char * movestring);
    void print();
    char * to_s();
    Square get_to_square();
    Square get_from_square();
    bool operator==(const Move & newmove);
    friend ostream & operator<<(ostream & out, const Move & amove);
};

vector<Move> add_vector(vector<Move> moves, vector<Move> tempmoves);

class State
{
  private:
    bool side_on_move;
    int round;
    char board[BOARD_SIZE_Y][BOARD_SIZE_X];
    bool game_over;

  public:
    State(); //constructor calls create_board
    void create_board();
    void print();
    void get_state(char board[BOARD_SIZE_Y][BOARD_SIZE_X]);
    void read_state(char newboard[BOARD_SIZE_Y][BOARD_SIZE_X]);
    bool square_is_empty(int x, int y);
    bool piece_is_white(int x, int y);
    bool piece_is_black(int x, int y);
    bool piece_is_color(int x, int y, bool color);
    bool piece_is_capturable(int x, int y, bool color);
    bool move_start_is_valid(int x0, int y0);
    vector<Move> move_gen(int x0, int y0, int dx, int dy, bool stop_short, bool capture);
    vector<Move> move_list(int x0, int y0);
    vector<Move> moves_for_side();
    void update_move_count();
    void update_side_on_move();
    State make_move(Move move);
    State human_move(string move, vector<Move> & themoves) throw (int);
    bool game_is_over();
    void king_queen_move(int x, int y, vector<Move> & moves, char piece);
    void bishop_rook_move(int x, int y, vector<Move> & moves, char piece);
    void knight_move(int x, int y, vector<Move> & moves);
    void pawn_move(int x, int y, vector<Move> & moves, char piece);
    int evaluate(bool side);
    Move choose_move() throw (int);
    bool is_final();
    bool on_move();
};

int negamax(State current_state, int depth, Move & best_move);
int human_play(State & board, vector<Move> & themoves);
int bot_play(State & board, vector<Move> & themoves);
int human_turn(State & board, vector<Move> & themoves);
int bot_turn(State & board, vector<Move> & themoves);


#endif
