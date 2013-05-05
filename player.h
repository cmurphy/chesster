#ifndef PLAYER_H
#define PLAYER_H

class Move;
class State;

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
