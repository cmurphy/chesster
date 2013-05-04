#include "player.h"

Player::Player(bool color)
{
  this->color = color;
}

bool Player::get_color()
{
  return color;
}

Move Player::make_move(State current)
{
  Move move(1, 0, 2, 2);
  return move;
}
