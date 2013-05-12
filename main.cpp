#include "header.h"
#include "imcs.h"
#include "player.h"
#include "game.h"

int main(int argc, char ** argv)
{
  bool verbose = false;
  if (argc > 1) {
    if (!strcmp(argv[1], "-v")) {
      verbose = true;
    }
  }
  Game game('W', verbose);
  game.play();
  return 0;
}

bool move_is_valid(string move)
{
  cout << move.length() << endl;
  return move.length() == 5 && move[0] >= 'a' && move[0] <= 'e' && move[1] >= '1' && move[1] <= '6' && move[2] == '-' && move[3] >= 'a' && move[3] <= 'e' && move[4] >= '1' && move[4] <= '6';
}
