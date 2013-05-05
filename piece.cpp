#include "piece.h"
#include "header.h"

bool piece_is_color(char p, bool color) 
{
  if (color == white) {
    return p >= 'B' && p <= 'R';
  } else {
    return p >= 'b' && p <= 'r';
  }
}

bool square_is_empty(char p)
{
  return p == '.';
}

bool piece_is_capturable(char p, bool color)
{
  if (color == white) {
    return piece_is_color(p, black);
  } else {
    return piece_is_color(p, white);
  }
}

bool move_start_is_valid(char p, bool color)
{
  return (p != '.' && piece_is_color(p, color));
}
