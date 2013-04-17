#include "header.h"

void swap(int & x, int & y)
{
  int tmp = x;
  x = y;
  y = tmp;
}

vector<Move> add_vector(vector<Move> oldv, vector<Move> newv)
{
  int vsize = newv.size();
  for(int i = 0; i < vsize; ++i) {
    oldv.push_back(newv[i]);
  }
  return oldv;
}

