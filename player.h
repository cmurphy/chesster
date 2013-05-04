#include "header.h"

class Player
{
  public:
    Player(bool color);
    Move make_move(State current);
    bool get_color();
  private:
    bool color;
};
