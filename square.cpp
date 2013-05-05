#include "square.h"

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
  cout << (int) (this->y + 1);
}

char * Square::to_s()
{
  char * square = new char[3];
  sprintf(square, "%c%d", (char) (this->x + 'a'), (int) (this->y + 1));
  return square;
}

bool Square::operator==(const Square & othersquare)
{
  return this->x == othersquare.x && this->y == othersquare.y;
}

ostream & operator<<(ostream & out, const Square & asquare)
{
  out << (char) (asquare.x + 'a');
  out << (int) (asquare.y + 1);
  return out;
}

void Square::getxy(int & x, int & y)
{
  x = this->x;
  y = this->y;
}
