#ifndef PLAYER_H
#define PLAYER_H

#include "header.h"

class Player
{
  public:
    Player(bool color);
    Move choose_move(State current);
    bool get_color();
  private:
    bool color;
};

#endif
