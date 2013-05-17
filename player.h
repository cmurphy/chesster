#ifndef PLAYER_H
#define PLAYER_H

class Move;
class State;

class Player
{
  public:
    Player(char color);
    Move choose_move(State current);
    char get_color();
    void set_color(char color);
  private:
    char color;
};

#endif
