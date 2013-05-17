#ifndef GAME_H
#define GAME_H

class State;
class Imcs;
class Player;

class Game
{
  public:
    Game(char color, bool verbose, bool offer);
    ~Game();
    void play();
  private:
    State * board;
    Imcs * server;
    Player * player;
};

#endif
