#ifndef ZOBRIST_H
#define ZOBRIST_H

class ZobristTable
{
  private:
    static long int table[30][13];
    static long int side[2];
  public:
    static void init();
    static long int lookup(int square, int piece);
    static long int lookup(bool side);
};
#endif
