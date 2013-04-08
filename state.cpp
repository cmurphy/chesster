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
//  for (int i = 0; i < 5; ++i) { board[1][i] = 'p'; }
  // blanks
// testing
  for (int i = 0; i < 5; ++i) { board[1][i] = '.'; }
  for (int i = 2; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      board[i][j] = '.';
    }
  }
  // white pawns
//  for (int i = 0; i < 5; ++i) { board[4][i] = 'P'; }
  // testing
  for (int i = 0; i < 5; ++i) { board[4][i] = '.'; }
  // white pieces
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

bool State::square_is_empty(int x, int y)
{
  return board[y][x] == '.';
}

bool State::piece_is_white(int x, int y)
{
  return board[y][x] >= 'B' && board[y][x] <= 'R';
}

bool State::piece_is_black(int x, int y)
{
  return board[y][x] >= 'b' && board[y][x] <= 'r';
}

bool State::piece_is_color(int x, int y, bool color)
{
  if (color == white) {
    return piece_is_white(x, y);
  } else {
    return piece_is_black(x, y);
  }
} 

bool State::piece_is_capturable(int x, int y, bool color)
{
  if(color == white) {
    return piece_is_black(x, y);
  } else {
    return piece_is_white(x, y);
  }
}

vector<Move> State::move_gen(int x0, int y0, int dx, int dy, bool stop_short = false, bool capture = true)
{
  int x = x0;
  int y = y0;
  bool color = piece_is_white(x, y);
  vector<Move> moves;
  do {
    x += dx;
    y += dy;
    if (x < 0 || x >= BOARD_SIZE_X || y < 0 || y >= BOARD_SIZE_Y) {
      break;
    }
    if (!square_is_empty(x, y)) {
      if (piece_is_color(x, y, color)) {
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
  char piece = board[y][x];
  vector<Move> moves, tempmoves;
  int dx = -1;
  int dy = -1;
  bool stop_short = false;
  bool capture = true;
  switch (piece) {
    /*************** king or queen ****************/
    case 'q':
    case 'k':
    case 'Q':
    case 'K':
    {
      while (dx <= 1) {
        while (dy <= 1) {
          if (dx == 0 && dy == 0) {
            dy++;
            continue;
          }
          stop_short = (piece == 'k' || piece == 'K');
          tempmoves = move_gen(x, y, dx, dy, stop_short);
          int vsize = tempmoves.size();
          for (int i = 0; i < vsize; ++i) {
            moves.push_back(tempmoves[i]);
          }
          ++dy;
        }
        ++dx;
        dy = -1;
      }
      break;
    }
    /*************** bishop or rook ****************/
    case 'r':
    case 'b':
    case 'R':
    case 'B':
    {
      dx = 1;
      dy = 0;
      stop_short = (piece == 'b' || piece == 'B');
      capture = (piece == 'r' || piece == 'R');
      for (int i = 1; i <= 4; ++i) {
        moves = add_vector(moves, move_gen(x, y, dx, dy, stop_short, capture));
        int tmp = dx;
        dx = dy;
        dy = tmp;
        dy = -dy;
      }
      if (piece == 'b' || piece == 'B') {
        dx = 1;
        dy = 1;
        stop_short = false;
        capture = true;
        for (int i = 1; i <= 4; ++i) {
          moves = add_vector(moves, move_gen(x, y, dx, dy, stop_short, capture));
          int tmp = dx;
          dx = dy;
          dy = tmp;
          dy = -dy;
        }
      }
      break;
    }
    /******************* pawn ******************/
    case 'p':
    case 'P':
    {
      int dir = 1;
      if (piece == 'P') {
        dir = -dir;
      }
      stop_short = true;
      tempmoves = move_gen(x, y, -1, dir, stop_short);
      if (tempmoves.size() == 1 && piece_is_capturable(tempmoves[0].get_to_square().x, tempmoves[0].get_to_square().y, (piece == 'P'))) {
        moves = add_vector(moves, tempmoves);
      }
      tempmoves = move_gen(x, y, 1, dir, stop_short);
      if (tempmoves.size() == 1 && piece_is_capturable(tempmoves[0].get_to_square().x, tempmoves[0].get_to_square().y, (piece == 'P'))) {
        moves = add_vector(moves, tempmoves);
      }
      capture = false;
      tempmoves = move_gen(x, y, 0, dir, stop_short, capture);
      moves = add_vector(moves, tempmoves);
      break;
    }
    default:
      cout << "fail" << endl;
  } 
  return moves;
}
