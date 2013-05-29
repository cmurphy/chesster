#include "state.h"
#include "header.h"
#include "move.h"
#include "piece.h"

State::State()
{
  create_board();
  game_over = false;
}

void State::create_board()
{
  side_on_move = white;
  round = 1;
  // black pieces
  board[0][0] = 'R';
  board[0][1] = 'N';
  board[0][2] = 'B';
  board[0][3] = 'Q';
  board[0][4] = 'K';
  // black pawns
  for (int i = 0; i < 5; ++i) { board[1][i] = 'P'; }
  // blanks
  for (int i = 2; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      board[i][j] = '.';
    }
  }

 // white pawns
  for (int i = 0; i < 5; ++i) { board[4][i] = 'p'; }
  // white pieces
  board[5][0] = 'k';
  board[5][1] = 'q';
  board[5][2] = 'b';
  board[5][3] = 'n';
  board[5][4] = 'r';
}

void State::print()
{
  cout << round << " ";
  if (side_on_move == white) {
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


bool State::on_move()
{
  return side_on_move;
}



vector<Move> State::move_gen(int x0, int y0, int dx, int dy, bool stop_short = false, bool capture = true)
{
  int x = x0;
  int y = y0;
  bool color = piece_is_color(board[y][x], white);
  vector<Move> moves;
  do {
    x += dx;
    y += dy;
    if (x < 0 || x >= BOARD_SIZE_X || y < 0 || y >= BOARD_SIZE_Y) {
      break;
    }
    if (!square_is_empty(board[y][x])) {
      if (piece_is_color(board[y][x], color)) {
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
  try {
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
        // fail
        throw 1;
    } 
  } catch (int e) {
    perror("Tried to add a move for a nonexistent piece.");
    exit(1);
  }
  return moves;
}

vector<Move> State::moves_for_side()
{
  vector<Move> themoves;
  for (int i = 0; i < BOARD_SIZE_X; ++i) {
    for (int j = 0; j < BOARD_SIZE_Y; ++j) {
      if (board[j][i] != '.' && piece_is_color(board[j][i], side_on_move)) {
        themoves = add_vector(themoves, move_list(i, j));
      }
    }
  }
  return themoves;
}

void State::update_move_count()
{
  ++round;
}

void State::update_side_on_move()
{
  side_on_move = !side_on_move;
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
    if (move_start_is_valid(board[fromy][fromx], side_on_move)) {
      newstate.read_state(this->board);
      if (toupper(board[toy][tox]) == 'K') {
        newstate.game_over = true;
      }
      char piece = newstate.board[fromy][fromx];
      newstate.board[fromy][fromx] = '.';
      newstate.board[toy][tox] = piece;
      newstate.round = round;
      newstate.side_on_move = side_on_move; // will be updated after move is made
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

bool State::game_is_over()
{
  if (round >= 40) {
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
      moves = add_vector(moves, tempmoves);
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
    if (piece_is_capturable(board[toy][tox], (piece == 'P'))) {
      moves = add_vector(moves, tempmoves);
    }
  }
  tempmoves = move_gen(x, y, 1, dir, stop_short);
  if (tempmoves.size() == 1) {
    tosquare = tempmoves[0].get_to_square();
    tosquare.getxy(tox, toy);
    if (piece_is_capturable(board[toy][tox], (piece == 'P'))) {
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
          whitescore += 1000;
          break;
        }
        case 'K':
        {
          whitescore += 5000;
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
          blackscore += 1000;
          break;
        }
        case 'k':
        {
          blackscore += 5000;
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

int g_max_depth;

Move State::choose_move() throw (int)
{
  vector<Move> themoves = moves_for_side();
  //TODO: On first move, computer always makes the same move. Change it up a bit.
  int size = themoves.size();
  State potential_state;
  Move newmove;
  if (size > 0) {
    int depth = 1;
    int value;
    int alpha_0;
    g_max_depth = depth;
    clock_t start = clock();
    clock_t time_now = start;
    int states_evaluated = 0;
    while (time_now - start < MAX_TIME) {
      value = -MAX_SCORE;
      alpha_0 = value;
      for (int i = 0; i < size; ++i) {
        int value_0 = max(value, -negamax(*this, depth, newmove, start, states_evaluated, -MAX_SCORE, -alpha_0));
        alpha_0 = max(alpha_0, value_0);
        if (value_0 > value) {
          newmove = themoves[i];
        }
        value = max(value, value_0);
      }
      ++depth;
      g_max_depth = depth;
      time_now = clock();
    }
    cout << "time: " << (time_now - start) / CLOCKS_PER_SEC << "seconds" << endl;
    cout << "states evaluated: " << states_evaluated << endl;
    Move empty_move;
    if (newmove == empty_move) {
        newmove = themoves[0];
    }
  }
  else {
    throw 1;
  }
  return newmove;
}



bool State::is_final()
{
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 5; ++j) {
      if (side_on_move == white && board[i][j] == 'K') {
        return false;
      }
      if (side_on_move == black && board[i][j] == 'k') {
        return false;
      }
    }
  }
  return true;
}
