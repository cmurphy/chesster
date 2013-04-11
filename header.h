#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const bool white = true;
const bool black = false;
const int MAX_MOVES = 40;
const int BOARD_SIZE_X = 5;
const int BOARD_SIZE_Y = 6;

void swap(int & x, int & y);
bool move_is_valid(string move);

class Square
{
  public:
    int x;
    int y;
    Square();
    Square(int x, int y);
    void print();
    bool operator==(const Square & othersquare);
};

class Move
{
  private:
    Square to_Square;
    Square from_Square;
  public:
    Move();
    Move(int x0, int y0, int xn, int yn);
    void print();
    Square get_to_square();
    Square get_from_square();
    bool operator==(const Move & newmove);
};

vector<Move> add_vector(vector<Move> moves, vector<Move> tempmoves);

class State
{
  private:
    bool move;
    int num_moves;
    char board[BOARD_SIZE_X][BOARD_SIZE_Y];
    bool game_over;

  public:
    State(); //constructor calls create_board
    void create_board();
    void print_state();
    void read_state(char newboard[BOARD_SIZE_X][BOARD_SIZE_Y]);
    bool square_is_empty(int x, int y);
    bool piece_is_white(int x, int y);
    bool piece_is_black(int x, int y);
    bool piece_is_color(int x, int y, bool color);
    bool piece_is_capturable(int x, int y, bool color);
    bool move_start_is_valid(int x0, int y0);
    vector<Move> move_gen(int x0, int y0, int dx, int dy, bool stop_short, bool capture);
    vector<Move> move_list(int x0, int y0);
    vector<Move> all_moves();
    State make_move(Move move);
    State human_move(string move, vector<Move> & themoves);
    bool game_is_over();
};

