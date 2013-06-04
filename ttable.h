#ifndef TTABLE_H
#define TTABLE_H
#include <math.h>

const int TTABLE_SIZE = 32768;
class TTableEntry;

class TTable
{
  private:
    static TTableEntry entries[TTABLE_SIZE];
  public:
    static TTableEntry * lookup(long int hash);
    static void save_entry(TTableEntry entry);
};
#endif
