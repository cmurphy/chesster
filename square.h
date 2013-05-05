#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
using namespace std;

class Square
{
  public:
    Square();
    Square(int x, int y);
    void print();
    char * to_s();
    bool operator==(const Square & othersquare);
    friend ostream & operator<<(ostream & out, const Square & asquare);
    void getxy(int & x, int & y);
  private:
    int x;
    int y;
};

#endif
