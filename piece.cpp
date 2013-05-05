#include "piece.h"
#include "header.h"

bool piece_is_color(char p, bool color) {
  if (color == white) {
    return p >= 'B' && p <= 'R';
  } else {
    return p >= 'b' && p <= 'r';
  }
}
