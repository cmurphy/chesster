#include "header.h"

int negamax(State current_state, int depth, Move & best_move)
{
  if (current_state.is_final() || depth <= 0) {
    return current_state.evaluate(current_state.on_move());
  }
  vector<Move> moves = current_state.moves_for_side();
  Move next_move = moves[0];
  State potential_state = current_state.make_move(next_move);
  int max = -(negamax(potential_state, depth - 1, best_move));
  int value;
  int size = moves.size();
  for (int i = 1; i < size; ++i) {
    next_move = moves[i];
    potential_state = current_state.make_move(next_move);
    value = -(negamax(potential_state, depth - 1, best_move));
    if (value > max) {
      max = value;
      best_move = next_move;
    }
  }
  return max;
}
