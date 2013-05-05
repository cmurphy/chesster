#include "player.h"
#include "state.h"
#include "move.h"

Player::Player(bool color)
{
  this->color = color;
}

bool Player::get_color()
{
  return color;
}

Move Player::choose_move(State current)
{
  try {
    Move move = current.choose_move();
    return move;
  } catch (int e) {
    perror ("No legal moves available.");
    exit(1);
  }
}
