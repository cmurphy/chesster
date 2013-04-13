#include "header.h"

Square::Square()
{
  this->x = 0;
  this->y = 0;
}

Square::Square(int x, int y)
{
  this->x = x;
  this->y = y;
}

void Square::print()
{
  cout << (char) (this->x + 'a');
  cout << (int) (this->y);
}

bool Square::operator==(const Square & othersquare)
{
  return this->x == othersquare.x && this->y == othersquare.y;
}

void Square::getxy(int & x, int & y)
{
  x = this->x;
  y = this->y;
}
