#include "header.h"
#include "imcs.h"
#include "player.h"
#include "game.h"
#include "cstdio"

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

void usage()
{
  cout << "USAGE: ./a.out [-v] [-c <color> ]"
       << "-v -- verbose"
       << "-o [color] -- offer, optional with color (W or B)"
       << "-a <gameid>  [color]-- accept a game with a given game id, optional with color (W or B)";
}


bool move_is_valid(const string move)
{
  string tmp_move(move, 0, 5);
  //cout << move.length() << endl;
  //return move.length() == 5 && move[0] >= 'a' && move[0] <= 'e' && move[1] >= '1' && move[1] <= '6' && move[2] == '-' && move[3] >= 'a' && move[3] <= 'e' && move[4] >= '1' && move[4] <= '6';
/*  cout << "tmp_move[0] >= 'a' " << (tmp_move[0] >= 'a') << endl;
  cout << "tmp_move[0] <= 'e' " << (tmp_move[0] <= 'e') << endl;
  cout << "tmp_move[1] >= '1' " << (tmp_move[1] >= '1') << endl;
  cout << "tmp_move[1] <= '6' " << (tmp_move[1] <= '6') << endl;
  cout << "tmp_move[2] == '-' " << (tmp_move[2] == '-') << endl;
  cout << "tmp_move[3] >= 'a' " << (tmp_move[3] >= 'a') << endl;
  cout << "tmp_move[3] <= 'e' " << (tmp_move[3] <= 'e') << endl;
  cout << "tmp_move[4] >= '1' " << (tmp_move[4] >= '1') << endl;
  cout << "tmp_move[4] <= '6' " << (tmp_move[5] <= '6') << endl; */
  return tmp_move[0] >= 'a' && tmp_move[0] <= 'e' && tmp_move[1] >= '1' && tmp_move[1] <= '6' && tmp_move[2] == '-' && tmp_move[3] >= 'a' && tmp_move[3] <= 'e' && tmp_move[4] >= '1' && tmp_move[4] <= '6';
  
}


int piece_value(char piece)
{
  switch(tolower(piece))
  {
    case '.':
      return 0;
    case 'p':
      return PAWN_VAL;
    case 'b':
      return BISHOP_VAL;
    case 'n':
      return KNIGHT_VAL;
    case 'r':
      return ROOK_VAL;
    case 'q':
      return QUEEN_VAL;
    case 'k':
      return KING_VAL;
    default:
      cout << "piece: " << piece;
      perror("Not a valid piece");
      exit(1);
  }
}

int piece_index(char piece)
{
  switch(piece)
  {
    case 'P':
      return 1;
    case 'B':
      return 2;
    case 'N':
      return 3;
    case 'R':
      return 4;
    case 'Q':
      return 5;
    case 'K':
      return 6;
    case 'p':
      return 7;
    case 'b':
      return 8;
    case 'n':
      return 9;
    case 'r':
      return 10;
    case 'q':
      return 11;
    case 'k':
      return 12;
    default:
      return 0;
  }
}
