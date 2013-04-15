#include "header.h"
#include <time.h>

int main()
{
  clock_t start = clock();
  State board;
  int x0 = 0, y0 = 0, dx = 1, dy = 1;
  bool stop_short = false, capture = true;
  int vsize;

  int random, index, size;
  Move move;
  vector<Move> themoves;
  string human_move;
  board.print_state();
  while (!board.game_is_over()) {

    /***** Human Move ******/
    themoves = board.moves_for_side();
    cout << "Human move!" << endl;
    cout << "Enter your move (in the form a1-b2)" << endl;
    cin >> human_move;
    cin.ignore(100, '\n');
    try {
      board = board.human_move(human_move, themoves);
    } catch (int e) {
      if (e == 1) {
        cout << "That string does not have a valid format. " << endl
             << "Please use the format 'a1-b2'." << endl;
        continue;
      } else if (e == 2) {
        cout << "You cannot move there. Try again." << endl;
        continue;
      } else {
        cout << "This exception hasn't been implemented yet." << endl;
        exit(1);
      }
    }
    board.print_state();

    if (board.game_is_over()) break;

    /***** Bot Move ******/
    themoves = board.moves_for_side();
    cout << "Bot move!" << endl;
    size = themoves.size();
    if (size != 0) {
      move = board.choose_move(themoves);
      board = board.make_move(move);
      board.print_state();
      cout << endl << endl;
      themoves = board.moves_for_side();
    }
    else {
      cout << "moves list had size 0" << endl;
    }
  }
  clock_t diff = clock() - start;
  diff = diff * 1000 / CLOCKS_PER_SEC;
  cout << diff/1000 << "seconds " << diff%1000 << "milliseconds" << endl;
  return 0;
} // endmain

vector<Move> add_vector(vector<Move> oldv, vector<Move> newv)
{
  int vsize = newv.size();
  for(int i = 0; i < vsize; ++i) {
    oldv.push_back(newv[i]);
  }
  return oldv;
}

void swap(int & x, int & y)
{
  int tmp = x;
  x = y;
  y = tmp;
}

bool move_is_valid(string move)
{
  return move.length() == 5 && move[0] >= 'a' && move[0] <= 'e' && move[1] >= '1' && move[1] <= '6' && move[2] == '-' && move[3] >= 'a' && move[3] <= 'e' && move[4] >= '1' && move[4] <= '6';
}
