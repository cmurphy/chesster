#include <iostream>
using namespace std;

const bool white = true;
const bool black = false;
const int MAX_MOVES = 40;
const int board_size_x = 5;
const int board_size_y = 6;

class State
{
  private:
    bool move;
    int num_moves;
    char board[board_size_x][board_size_y];

  public:
    State(); //constructor calls create_board
    void create_board();
    void print_state();
    void read_state(char newboard[board_size_x][board_size_y]);
};
