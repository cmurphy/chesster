#ifndef MOVE_H
#define MOVE_H

#include "square.h"
#include <vector>

class Move
{
  private:
    Square to_Square;
    Square from_Square;
  public:
    Move();
    Move(int x0, int y0, int xn, int yn);
    Move(char * movestring);
    void print();
    char * to_s();
    Square get_to_square();
    Square get_from_square();
    bool operator==(const Move & newmove);
    friend ostream & operator<<(ostream & out, const Move & amove);
};

vector<Move> add_vector(vector<Move> moves, vector<Move> tempmoves);

#endif
