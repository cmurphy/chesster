#include "header.h"

int main()
{
  State board;
  board.print_state();
  int x0 = 0, y0 = 0, dx = 1, dy = 1;
  bool stop_short = false, capture = true;

  vector<Move> black_king_moves = board.move_list(x0, y0);
  int vsize = black_king_moves.size();
  cout << "Black king's moves: \n";
  for (int i = 0; i < vsize; ++i) {
    black_king_moves[i].print();
  }

  vector<Move> black_queen_moves = board.move_list(1, 0);
  vsize = black_queen_moves.size();
  cout << "Black queen's moves: \n";
  for (int i = 0; i < vsize; ++i) {
    black_queen_moves[i].print();
  }

  vector<Move> black_pawn_moves;
  for (int i = 0; i < 5; ++i) {
    black_pawn_moves = add_vector(black_pawn_moves, board.move_list(i, 1));
  }
  vsize = black_pawn_moves.size();
  cout << "Black pawns' moves: \n";
  for (int i = 0; i < vsize; ++i) {
    black_pawn_moves[i].print();
  }

  vector<Move> white_pawn_moves;
  for (int i = 0; i < 5; ++i) {
    white_pawn_moves = add_vector(white_pawn_moves, board.move_list(i, 4));
  }
  vsize = white_pawn_moves.size();
  cout << "White pawns' moves: \n";
  for (int i = 0; i < vsize; ++i) {
    white_pawn_moves[i].print();
  }
  
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

vector<Move> add_vector(vector<Move> oldv, vector<Move> newv)
{
  int vsize = newv.size();
  for(int i = 0; i < vsize; ++i) {
    oldv.push_back(newv[i]);
  }
  return oldv;
}
