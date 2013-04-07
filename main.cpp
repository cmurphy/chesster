#include "header.h"

int main()
{
  State board;
  board.print_state();
  char newboard[5][6];
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 5; ++j) {
      newboard[i][j] = '.';
    }
  }
//  board.read_state(newboard);
//  board.print_state();
  int x0 = 0, y0 = 0, dx = 1, dy = 1;
  bool stop_short = false, capture = true;
//  board.move_gen(x0, y0, dx, dy, stop_short, capture);
  vector<Move> moves = board.move_list(x0, y0);
  Move move = moves[0];
  move.print();
  cout << "end of main" << endl;
  return 0;
}

bool is_color(char piece, bool color)
{
  if (piece >= 'B' && piece <= 'Q') {
    if (color == white) {
      return true;
    }
  }
  else if (piece >= 'b' && piece <= 'q') {
    if (color == black) {
      return true;
    }
  }
  return false;
}

bool is_empty(char piece)
{
  return piece == '.';
}
