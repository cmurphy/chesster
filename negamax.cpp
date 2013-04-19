#include "header.h"

int negamax(State current_state, int depth, Move & final_best_move)
{
//  cout << "Depth: " << depth << endl;
  if (current_state.is_final() || depth <= 0) {
    return current_state.evaluate(current_state.on_move());
  }
  vector<Move> moves = current_state.moves_for_side();
  Move next_move = moves[0];
  Move best_move;
  State potential_state = current_state.make_move(next_move);
  potential_state.update_side_on_move();
//  cout << "Evaluating potential state for move ";
//  next_move.print();
//  cout << "(0)" << endl;
  int max = -(negamax(potential_state, depth - 1, final_best_move));
  int value;
  int size = moves.size();
  for (int i = 1; i < size; ++i) {
    next_move = moves[i];
//    cout << "Evaluating potential state for move ";
//    next_move.print();
//    cout << "(" << i << ")" << endl;
    potential_state = current_state.make_move(next_move);
    value = -(negamax(potential_state, depth - 1, final_best_move));
//    cout << "Value of negamax at depth " << depth << ": " << value << endl;
    if (value > max) {
      max = value;
      best_move = next_move;
//      cout << "******************************************";
//      cout << "new best move: ";
//      best_move.print();
//      cout << "******************************************";
//      cout << endl;
    }
  }
  final_best_move = best_move;
  return max;
}
