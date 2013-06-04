#include "move.h"
#include <cstdio>

Move::Move()
{
}

Move::Move(int x0, int y0, int xn, int yn)
{
  to_Square = Square(xn, yn);
  from_Square = Square(x0, y0);
}

Move::Move(char * movestring)
{
  // Assumes validation beforehand
  // TODO: shouldn't assume
  int from_col = movestring[0] - 'a';
  int from_row = movestring[1] - '1';
  int to_col = movestring[3] - 'a';
  int to_row = movestring[4] - '1';
  to_Square = Square(to_col, to_row);
  from_Square = Square(from_col, from_row);
}

void Move::print()
{
  from_Square.print();
  cout << "->";
  to_Square.print();
}

char * Move::to_s()
{
  char * move = new char[6];
  sprintf(move, "%s-%s", from_Square.to_s(), to_Square.to_s());
  return move;
}

Square Move::get_to_square()
{
  return to_Square;
}

Square Move::get_from_square()
{
  return from_Square;
}

bool Move::operator==(const Move & othermove)
{
  return this->to_Square == othermove.to_Square && this->from_Square == othermove.from_Square;
}

ostream & operator<<(ostream & out, const Move & amove)
{
  out << amove.from_Square;
  out << "-";
  out << amove.to_Square;
  return out;
}
