#include "ttable.h"
#include "ttable_entry.h"

TTableEntry TTable::entries[TTABLE_SIZE];

TTableEntry * TTable::lookup(long int hash)
{
  int index = hash & 0x7ffffffff; // for < 4 * pow(2, 32)
  if (entries[index].is_valid()) {
    return &(entries[index]);
  } return 0;
}

void TTable::save_entry(TTableEntry entry)
{
  int index = entry.get_hash() & 0x7ffffffff;
  entries[index] = entry;
}
