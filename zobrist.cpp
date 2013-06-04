#include "zobrist.h"
#include <cstdlib>
#include <time.h>

long int ZobristTable::table[30][13];
long int ZobristTable::side[2];

void ZobristTable::init()
{
  srand(time(NULL));

  for (int i = 0; i < 30; ++i) {
    for (int j = 0; j < 13; ++j) {
      long int tmp1 = rand();
      long int tmp2 = rand();
      table[i][j] = tmp1 * tmp2; // multiply to make it "long"er
    }
  }

  for (int i = 0; i < 2; ++i) {
    long int tmp1 = rand();
    long int tmp2 = rand();
    side[i] = tmp1 * tmp2;
  }
}


long int ZobristTable::lookup(int square, int piece)
{
  return table[square][piece];
}


long int ZobristTable::lookup(bool side_on_move)
{
  return side[side_on_move];
}
