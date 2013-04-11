#include "header.h"

int main()
{
  State board;
  board.print_state();
  int x0 = 0, y0 = 0, dx = 1, dy = 1;
  bool stop_short = false, capture = true;
  int vsize;
/*
  vector<Move> black_king_moves = board.move_list(x0, y0);
  vsize = black_king_moves.size();
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

  vector<Move> white_bishop_moves = board.move_list(2, 5);
  vsize = white_bishop_moves.size();
  cout << "White bishops' moves: \n";
  for (int i = 0; i < vsize; ++i) {
    white_bishop_moves[i].print();
  }

  vector<Move> black_bishop_moves = board.move_list(2, 0);
  vsize = black_bishop_moves.size();
  cout << "Black bishops' moves: \n";
  for (int i = 0; i < vsize; ++i) {
    black_bishop_moves[i].print();
  }

  vector<Move> white_rook_moves = board.move_list(0, 5);
  vsize = white_rook_moves.size();
  cout << "White rooks' moves: \n";
  for (int i = 0; i < vsize; ++i) {
    white_rook_moves[i].print();
  }

  vector<Move> black_rook_moves = board.move_list(4, 0);
  vsize = black_rook_moves.size();
  cout << "Black rooks' moves: \n";
  for (int i = 0; i < vsize; ++i) {
    black_rook_moves[i].print();
  }


  vector<Move> white_knight_moves = board.move_list(3, 0);
  vsize = white_knight_moves.size();
  cout << "White knight's moves: \n";
  for (int i = 0; i < vsize; ++i) {
    white_knight_moves[i].print();
  }

  // Generate black knight moves
  vector<Move> black_knight_moves = board.move_list(1, 5);
  vsize = black_knight_moves.size();
  cout << "Black knight's moves: \n";
  for (int i = 0; i < vsize; ++i) {
    black_knight_moves[i].print();
  }

  // Move the black knight
  State newboard = board.make_move(black_knight_moves[0]);
  newboard.print_state();

  // Before each move, should generate a list of all valid moves by adding up each move vector it found
  vector<Move> themoves = board.all_moves();
  State newboard = board.human_move("b2-b3", themoves);
  newboard.print_state();
*/
/*
  board.print_state();
  srand(time(0));
  int random, index;
  vector<Move> themoves = board.all_moves();
  Move move;
  board.print_state();
  while (!board.game_is_over()) {
    random = rand();
    index = random % themoves.size();
    move = themoves[index];
    board = board.make_move(move);
    board.print_state();
    themoves = board.all_moves();
  } */
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

// Dinky user input validation
// Should probably be implemented with regex if time
bool move_is_valid(string move)
{
  return move.length() == 5 && move[0] >= 'a' && move[0] <= 'e' && move[1] >= '1' && move[1] <= '6' && move[2] == '-' && move[3] >= 'a' && move[3] <= 'e' && move[4] >= '1' && move[4] <= '6';
}
