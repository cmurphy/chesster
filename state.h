#ifndef STATE_H
#define STATE_H

#include <vector>
using namespace std;

const int BOARD_SIZE_X = 5;
const int BOARD_SIZE_Y = 6;

class Move;

class State
{
  private:
    bool side_on_move;
    int round;
    char board[BOARD_SIZE_Y][BOARD_SIZE_X];
    bool game_over;
    int state_value;

  public:
    State(); 
    void create_board();
    void print();
    void read_state(char newboard[BOARD_SIZE_Y][BOARD_SIZE_X]);
    vector<Move> move_gen(int x0, int y0, int dx, int dy, bool stop_short, bool capture);
    vector<Move> move_list(int x0, int y0);
    vector<Move> moves_for_side();
    void update_move_count();
    void update_side_on_move();
    bool on_move();
    char make_move(Move move);
    void unmake_move(Move move, char captured);
    //State human_move(string move, vector<Move> & themoves) throw (int);
    bool game_is_over();
    bool is_final();
    void king_queen_move(int x, int y, vector<Move> & moves, char piece);
    void bishop_rook_move(int x, int y, vector<Move> & moves, char piece);
    void knight_move(int x, int y, vector<Move> & moves);
    void pawn_move(int x, int y, vector<Move> & moves, char piece);
    int evaluate();
    int evaluate(bool side);
    Move choose_move() throw (int);
};

#endif
