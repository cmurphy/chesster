#include "header.h"

State::State()
{
  create_board();
  game_over = false;
}

void State::create_board()
{
  move = white;
  num_moves = 0;
  // black pieces
  board[0][0] = 'R';
  board[0][1] = 'N';
  board[0][2] = 'B';
  board[0][3] = 'Q';
  board[0][4] = 'K';
  // black pawns
  for (int i = 0; i < 5; ++i) { board[1][i] = 'P'; }
  // blanks
//  for (int i = 0; i < 5; ++i) { board[1][i] = '.'; }
  for (int i = 2; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      board[i][j] = '.';
    }
  }

 // white pawns
  for (int i = 0; i < 5; ++i) { board[4][i] = 'p'; }
  // testing
//  for (int i = 0; i < 5; ++i) { board[4][i] = '.'; }
  // white pieces
  board[5][0] = 'k';
  board[5][1] = 'q';
  board[5][2] = 'b';
  board[5][3] = 'n';
  board[5][4] = 'r';
}

void State::print_state()
{
  cout << num_moves << " ";
  if (move == white) {
    cout << "W" << endl;
  } else {
    cout << "B" << endl;
  }
  for (int i = 5; i >= 0; --i) {
    for (int j = 0; j < 5; ++j) {
      cout << board[i][j];
    }
    cout << endl;
  }
}

void State::read_state(char newboard[BOARD_SIZE_Y][BOARD_SIZE_X])
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

bool State::move_start_is_valid(int x0, int y0)
{
  return (board[y0][x0] != '.' && piece_is_color(x0, y0, move));
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
  int dx = -1;
  int dy = -1;
  vector<Move> moves, tempmoves;
  bool stop_short = false;
  bool capture = true;
  switch (piece) {
    case 'q':
    case 'k':
    case 'Q':
    case 'K':
    {
      king_queen_move(x, y, moves, piece);
      break;
    }
    case 'r':
    case 'b':
    case 'R':
    case 'B':
    {
      bishop_rook_move(x, y, moves, piece);
      break;
    }
    case 'n':
    case 'N':
    {
      knight_move(x, y, moves);
      break;
    }
    case 'p':
    case 'P':
    {
          pawn_move(x, y, moves, piece);
          break;
    }
    default:
      // should probably throw an exception
      cout << "fail" << endl;
  } 
  return moves;
}

vector<Move> State::moves_for_side()
{
  vector<Move> themoves;
  for (int i = 0; i < BOARD_SIZE_X; ++i) {
    for (int j = 0; j < BOARD_SIZE_Y; ++j) {
      if (board[j][i] != '.' && piece_is_color(i, j, move)) {
        themoves = add_vector(themoves, move_list(i, j));
      }
    }
  }
  return themoves;
}

State State::make_move(Move newmove)
{
  Square from = newmove.get_from_square();
  Square to = newmove.get_to_square();
  int fromx, fromy, tox, toy;
  from.getxy(fromx, fromy);
  to.getxy(tox, toy);
  State newstate;
  try {
    if (move_start_is_valid(fromx, fromy)) {
      newstate.read_state(this->board);
      if (toupper(board[toy][tox]) == 'K') {
        newstate.game_over = true;
      }
      char piece = newstate.board[fromy][fromx];
      newstate.board[fromy][fromx] = '.';
      newstate.board[toy][tox] = piece;
      newstate.move = !move;
      newstate.num_moves = num_moves + 1;
      if (piece == 'p' && toy == 0) {
        newstate.board[toy][tox] = 'q';
      }
      if (piece == 'P' && toy == 5) {
        newstate.board[toy][tox] = 'Q';
      }
    } else {
      int e = 1;
      throw e;
    }
  } catch (int e) {
    cout << "Not a valid move.\n";
  }
  return newstate;
}

State State::human_move(string move, vector<Move> & themoves) throw (int)
{
  if (!move_is_valid(move)) { // only checks for validity of string, should check for validity of move
    throw 1; // Move string is not valid
  }
  else {
    int from_col = move[0] - 'a';
    int from_row = move[1] - '1';
    int to_col = move[3] - 'a';
    int to_row = move[4] - '1';
    Move newmove(from_col, from_row, to_col, to_row);
    // Check if move is a valid move
    vector<Move>::iterator i = find(themoves.begin(), themoves.end(), newmove);
    if (i != themoves.end()) {
      cout << "making a move" << endl;
      return make_move(newmove);
    }
    else {
      throw 2; // Move was not in valid moves list
    }
  }
}

// Scans the board looking for a king or if 40 moves have been played
bool State::game_is_over()
{
  if (num_moves >= 40) {
    return true;
  }
  if (game_over) {
    return true;
  }
  return false;
}

void State::king_queen_move(int x, int y, vector<Move> & moves, char piece)
{
  vector<Move> tempmoves;
  bool stop_short;
  for(int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      if (dx == 0 && dy == 0) {
        continue;
      }
      stop_short = (piece == 'k' || piece == 'K');
      tempmoves = move_gen(x, y, dx, dy, stop_short);
      int vsize = tempmoves.size();
      add_vector(moves, tempmoves);
    }
  } 
}

void State::bishop_rook_move(int x, int y, vector<Move> & moves, char piece)
{
  int dx = 1;
  int dy = 0;
  bool stop_short = (piece == 'b' || piece == 'B');
  bool capture = (piece == 'r' || piece == 'R');
  for (int i = 1; i <= 4; ++i) {
    moves = add_vector(moves, move_gen(x, y, dx, dy, stop_short, capture));
    swap(dx, dy);
    dy = -dy;
  }
}

void State::knight_move(int x, int y, vector<Move> & moves)
{
  int dx = 1;
  int dy = 2;
  bool stop_short = true;
  for (int i = 1; i <= 4; ++i) {
    moves = add_vector(moves, move_gen(x, y, dx, dy, stop_short));
    swap(dx, dy);
    dy = -dy;
  }
  dx = -1;
  dy = 2;
  for (int i = 1; i <= 4; ++i) {
    moves = add_vector(moves, move_gen(x, y, dx, dy, stop_short));
    swap(dx, dy);
    dy = -dy;
  }
}

void State::pawn_move(int x, int y, vector<Move> & moves, char piece)
{
  int dir = 1;
  if (piece == 'p') {
    dir = -dir;
  }
  bool stop_short = true;
  vector<Move> tempmoves = move_gen(x, y, -1, dir, stop_short);
  
  int tox, toy;
  Square tosquare;
  if (tempmoves.size() == 1) {
    tosquare = tempmoves[0].get_to_square();
    tosquare.getxy(tox, toy);
    if (piece_is_capturable(tox, toy, (piece == 'P'))) {
      moves = add_vector(moves, tempmoves);
    }
  }
  tempmoves = move_gen(x, y, 1, dir, stop_short);
  if (tempmoves.size() == 1) {
    tosquare = tempmoves[0].get_to_square();
    tosquare.getxy(tox, toy);
    if (piece_is_capturable(tox, toy, (piece == 'P'))) {
      moves = add_vector(moves, tempmoves);
    }
  }
  bool capture = false;
  tempmoves = move_gen(x, y, 0, dir, stop_short, capture);
  moves = add_vector(moves, tempmoves);
}

int State::evaluate(bool side)
{
  int whitescore = 0, blackscore = 0;
  char piece;
  for(int i = 0; i < 6; ++i) {
    for(int j = 0; j < 5; ++j) {
      piece = board[i][j];
      switch(piece) {
        case 'P':
        {
          whitescore += 100;
          break;
        }
        case 'B':
        case 'N':
        {
          whitescore += 300;
          break;
        }
        case 'R':
        {
          whitescore += 500;
          break;
        }
        case 'Q':
        {
          whitescore += 900;
          break;
        }
        case 'p':
        {
          blackscore += 100;
          break;
        }
        case 'b':
        case 'n':
        {
          blackscore += 300;
          break;
        }
        case 'r':
        {
          blackscore += 500;
          break;
        }
        case 'q':
        {
          blackscore += 900;
          break;
        }
        default:
        {
          break;
        }
      }
    }
  }
  if (side == white) {
    return whitescore - blackscore;
  }
  return blackscore - whitescore;
}

Move State::choose_move(vector<Move> & themoves)
{
  //TODO: On first move, computer always makes the same move. Change it up a bit.
  int size = themoves.size();
  State potential_state;
  Move newmove;
    if (size > 0) {
      potential_state = make_move(themoves[0]);
      int tmpscore = potential_state.evaluate(!move);
      int score = tmpscore;
      newmove = themoves[0];
      for (int i = 1; i < size; ++i) {
        potential_state = this->make_move(themoves[i]);
        tmpscore = potential_state.evaluate(!move);
        if (tmpscore < score) {
          score = tmpscore;
          newmove = themoves[i];
        }
      }
    }
    else {
      //throw error
    }
  return newmove;
}
