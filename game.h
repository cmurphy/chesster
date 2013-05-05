#ifndef GAME_H
#define GAME_H

class State;
class Imcs;
class Player;

class Game
{
  public:
    Game(bool color);
    ~Game();
    void play();
  private:
    State * board;
    Imcs * server;
    Player * player;
};

#endif
