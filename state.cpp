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
#include "state.h"

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
  // white pawns
  for (int i = 0; i < 5; ++i) { board[4][i] = 'P'; }
  // white piaces
  board[5][0] = 'K';
  board[5][1] = 'Q';
  board[5][2] = 'B';
  board[5][3] = 'N';
  board[5][4] = 'R';
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
