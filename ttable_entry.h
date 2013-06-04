#ifndef TTABLE_ENTRY_H
#define TTABLE_ENTRY_H

class TTableEntry
{
  private:
    long int hash;
    int a;
    int b;
    int value;
    bool valid;
    int depth;
  public:
    TTableEntry();
    TTableEntry(long int hash, int a, int b, int value, bool valid);
    long int get_hash();
    bool is_valid();
    bool is_within_cutoff(int alpha, int beta, int depth);
    int get_value();
};
#endif
