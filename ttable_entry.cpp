#include "ttable_entry.h"

TTableEntry::TTableEntry()
{
  hash = a = b = value = 0;
  valid = false;
}

TTableEntry::TTableEntry(long int hash, int a, int b, int value, bool valid)
{
  this->hash = hash;
  this->a = a;
  this->b = b;
  this->value = value;
  valid = true;
}

long int TTableEntry::get_hash()
{
  return hash;
}

bool TTableEntry::is_valid()
{
  return valid;
}

bool TTableEntry::is_within_cutoff(int alpha, int beta, int depth)
{
  return ((a < value && value < b) || (a <= alpha && beta <= b)) && this->depth >= depth;
}

int TTableEntry::get_value()
{
  return value;
}
