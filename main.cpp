#include "header.h"
#include "imcs.h"
#include "player.h"
#include "game.h"

int main(int argc, char ** argv)
{
  bool verbose = false;
  char player_color = '?';
  bool offer = true;
  int game_id = 0;
  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      if (!strcmp(argv[i], "-v")) {
        verbose = true;
      }
      else if (!strcmp(argv[i], "-o")) {
        if (i+1 < argc && argv[i+1][0] != 'W' && argv[i+1][0] != 'B' && argv[i+1][0] != '-') {
          usage();
        } else {
          if (i+1 < argc && argv[i+1][0] != '-') {
            player_color = argv[i+1][0];
            ++i;
          }
          offer = true;
        }
      }
      else if (!strcmp(argv[i], "-a")) {
        if (i+1 < argc && atoi(argv[i+1]) != 0) {
          game_id = atoi(argv[i+1]);
          if (i+2 < argc && (argv[i+2][0] == 'W' || argv[i+2][0] == 'B')) {
            player_color = argv[i+2][0];
          }
          offer = false;
        } else {
          usage();
        }
      }
    }
  }
  Game game(player_color, verbose, offer, game_id);
  game.play();
  return 0;
}

bool move_is_valid(string move)
{
  cout << move.length() << endl;
  return move.length() == 5 && move[0] >= 'a' && move[0] <= 'e' && move[1] >= '1' && move[1] <= '6' && move[2] == '-' && move[3] >= 'a' && move[3] <= 'e' && move[4] >= '1' && move[4] <= '6';
}

void usage()
{
  cout << "USAGE: ./a.out [-v] [-c <color> ]"
       << "-v -- verbose"
       << "-o -- offer, optional with color (W or B)";
}
