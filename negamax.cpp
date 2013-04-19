#include "header.h"

int negamax(State current_state, int depth, Move & final_best_move)
{
  if (current_state.is_final() || depth <= 0) {
    int eval = current_state.evaluate(current_state.on_move());
    #ifdef DEBUG
      cout << eval << endl;
    #endif
    return eval;
  }
  vector<Move> moves = current_state.moves_for_side();
  Move next_move = moves[0];
  Move best_move;
  State potential_state = current_state.make_move(next_move);
  potential_state.update_side_on_move();
  #ifdef DEBUG
    cout << endl;
    for (int i = depth; i < MAX_DEPTH; ++i) { cout << "\t"; }
    if (current_state.on_move() == white) {
      cout << "<move-white " << next_move << ">";
    } else {
      cout << "<move-black " << next_move << ">";
    } 
  #endif
  int max = -(negamax(potential_state, depth - 1, final_best_move));
  int value;
  int size = moves.size();
  for (int i = 1; i < size; ++i) {
    next_move = moves[i];
    potential_state = current_state.make_move(next_move);
    potential_state.update_side_on_move();
    #ifdef DEBUG
      for (int i = depth; i < MAX_DEPTH; ++i) { cout << "\t"; }
      if (current_state.on_move() == white) {
        cout << "<move-white " << next_move << ">";
      } else {
        cout << "<move-black " << next_move << ">";
      } 
    #endif
    value = -(negamax(potential_state, depth - 1, final_best_move));
    //cout << value << endl;
    if (value > max) {
      max = value;
      best_move = next_move;
    }
  }
  #ifdef DEBUG
    bool move = current_state.on_move();
    cout << endl;
    for (int i = depth; i < MAX_DEPTH; ++i) { cout << "\t"; }
    if (move == white) { cout << "Best white score: "; }
    else { cout << "Best black score: "; }
    cout << max;
    cout << endl;
  #endif
  final_best_move = best_move;
  return max;
}
