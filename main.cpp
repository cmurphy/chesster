#include "header.h"
#include <time.h>

int main(int argc, char * argv[])
{
  bool botplay = false;
  // Deal with optional arguments, if any
  if (argc > 1) {
    if (strcmp(argv[1], "--botplay")) {
      botplay = true;
    }
    else {
      cout << "Usage: ./a.out [--botplay]" << endl;
      exit(0);
    }
  }
  clock_t start = clock();
  int x0 = 0, y0 = 0, dx = 1, dy = 1;
  bool stop_short = false, capture = true;
  int vsize;

  State board;
  vector<Move> themoves;
  int random, index, size;
  Move move;
  board.print_state();
  int game_over = 1;
  while (!board.game_is_over()) {

    if (botplay) {
    }
    else {
      game_over = human_play(board, themoves);
      if (game_over == 1) {
        continue;
      }
      else if (game_over == 0) {
        break;
      }
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

// Return 0 if game is over, return 1 if loop should continue
int human_play(State & board, vector<Move> & themoves)
{
  int size;
  // ***** Human Move ****** /
  int turn_value = human_turn(board, themoves);
  if (turn_value != 2) {
    return turn_value;
  }

  if (board.game_is_over()) return 0;

  // ***** Bot Move ****** /
  themoves = board.moves_for_side();
  cout << "Bot move!" << endl;
  size = themoves.size();
  Move move;
  if (size != 0) {
    try {
      move = board.choose_move(themoves);
    } catch (int e) {
      // No more moves
      cout << "There are no more moves! Stalemate." << endl;
      return 0;
    }
    board = board.make_move(move);
    board.update_move_count();
    board.print_state();
    cout << endl << endl;
    themoves = board.moves_for_side();
  }
  else {
    cout << "moves list had size 0" << endl;
  }

}

int bot_play(State & board, vector<Move> & themoves)
{

}

int human_turn(State & board, vector<Move> & themoves)
{
  string human_move;
  Move move;
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
      return 1; // Return to calling function which loops over this play
    } else if (e == 2) {
      cout << "You cannot move there. Try again." << endl;
      return 1;
    } else {
      cout << "This exception hasn't been implemented yet." << endl;
      exit(1);
    }
  }
  board.print_state();
  cout << endl;
  return 2; // exit normally
}
