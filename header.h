#include <iostream>
#include <vector>
using namespace std;

const bool white = true;
const bool black = false;
const int MAX_MOVES = 40;
const int BOARD_SIZE_X = 5;
const int BOARD_SIZE_Y = 6;

//bool is_color(char piece, bool color);
//bool is_empty(char piece);
void swap(int & x, int & y);

class Square
{
  public:
    int x;
    int y;
    Square();
    Square(int x, int y);
    void print();
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
};

vector<Move> add_vector(vector<Move> moves, vector<Move> tempmoves);

class State
{
  private:
    bool move;
    int num_moves;
    char board[BOARD_SIZE_X][BOARD_SIZE_Y];

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
    vector<Move> move_gen(int x0, int y0, int dx, int dy, bool stop_short, bool capture);
    vector<Move> move_list(int x0, int y0);
};

