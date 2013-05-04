#include "header.h"
#include "imcs.h"
#include "player.h"

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
