#include "header.h"

Move::Move()
{
}

Move::Move(int x0, int y0, int xn, int yn)
{
  to_Square = Square(xn, yn);
  from_Square = Square(x0, y0);
}

void Move::print()
{
  from_Square.print();
  cout << "->";
  to_Square.print();
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
