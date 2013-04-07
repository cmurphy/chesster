/*
    The state class represents the minichess board. 
    Members: 
      - a two-dimentional array to represent the 5x6 area board
      - boolean who's move
      - number of moves played (max 40)
    Methods:
      - print the current state of the board
      - read the current board from a stream
      - create a starting board
*/
#include "header.h"

State::State()
{
  create_board();
}

void State::create_board()
{
  move = white;
  num_moves = 0;
  // black pieces
  board[0][0] = 'k';
  board[0][1] = 'q';
  board[0][2] = 'b';
  board[0][3] = 'n';
  board[0][4] = 'r';
  // black pawns
  for (int i = 0; i < 5; ++i) { board[1][i] = 'p'; }
  // blanks
  for (int i = 2; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      board[i][j] = '.';
    }
  }
  // testing
  board[1][0] = '.';
  // white pawns
  for (int i = 0; i < 5; ++i) { board[4][i] = 'P'; }
  // white piaces
  board[5][0] = 'R';
  board[5][1] = 'N';
  board[5][2] = 'B';
  board[5][3] = 'Q';
  board[5][4] = 'K';
}

void State::print_state()
{
  cout << num_moves << " ";
  if (move == white) {
    cout << "W" << endl;
  } else {
    cout << "B" << endl;
  }
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 5; ++j) {
      cout << board[i][j];
    }
    cout << endl;
  }
}

void State::read_state(char newboard[BOARD_SIZE_X][BOARD_SIZE_Y])
{
  for (int i = 0; i < BOARD_SIZE_Y; ++i) {
    for (int j = 0; j < BOARD_SIZE_X; ++j) {
      board[i][j] = newboard[i][j];
    }
  }
}

vector<Move> State::move_gen(int x0, int y0, int dx, int dy, bool stop_short, bool capture)
{
  int x = x0;
  int y = y0;
  bool color = move;
  vector<Move> moves;
  do {
    cout << "in move gen" << endl;
    x += dx;
    y += dy;
    if (x < 0 || x > BOARD_SIZE_X || y < 0 || y > BOARD_SIZE_Y) {
      break;
    }
    if (!is_empty(board[x][y])) {
      if (is_color(board[x][y], color)) {
        break;
      }
      if (!capture) {
        break;
      }
      stop_short = true;
    }
    Move move(x0, y0, x, y);
    moves.push_back(move);
  } while (!stop_short); 
  return moves;
}

vector<Move> State::move_list(int x, int y)
{
  char piece = board[x][y];
  vector<Move> moves;
  int dx = -1;
  int dy = -1;
  bool stop_short = false;
  switch (piece) {
    case 'q':
    case 'k':
    case 'Q':
    case 'K':
      while (dx <= 1) {
        while (dy <= 1) {
          if (dx == 0 && dy == 0) {
            dy++;
            continue;
          }
          stop_short = (piece == 'k' || piece == 'K');
          vector<Move> tempmoves = move_gen(x, y, dx, dy, stop_short, true);
          int vsize = tempmoves.size();
          for (int i = 0; i < vsize; ++i) {
            moves.push_back(tempmoves[i]);
          }
          ++dy;
        }
        ++dx;
        dy = -1;
      }
      return moves;
      break;
    default:
      cout << "fail" << endl;
  } 
}
