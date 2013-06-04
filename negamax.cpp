//TODO: Right now negamax will avoid making a good move now in favor of
// what it thinks is a possible better move in the future. If it 
// doesn't see any good moves in the future, it will take the first
// move in the list, which is usually useless. Add logic and 
// randomization to make better moves. Also make better evaluator.

#include "header.h"
#include "state.h"
#include "move.h"
#include "ttable.h"
#include "ttable_entry.h"

int negamax(State current_state, int depth, clock_t start_time, int & states_evaluated, int alpha, int beta)
{
  if (current_state.is_final() || depth <= 0) {
//    int eval = current_state.evaluate(current_state.on_move());
    int eval = current_state.evaluate();
    #ifdef DEBUG
      cout << eval << endl;
    #endif
    ++states_evaluated;
    return eval;
  }
  long int hash = current_state.get_hash();
  TTableEntry * table_entry = TTable::lookup(hash);
  if (table_entry != 0 && table_entry->is_within_cutoff(alpha, beta, depth)) {
    return table_entry->get_value();
  }
  int value = -MAX_SCORE;
  int alpha_0 = alpha;
  Move next_move;
  Move best_move;
  vector<Move> moves = current_state.moves_for_side();
  int size = moves.size();
  #ifdef DEBUG
    State potential_state = current_state;
  #endif
  for (int i = 0; i < size; ++i) {
    next_move = moves[i];
    char captured = current_state.make_move(next_move);
    current_state.update_side_on_move();
    #ifdef DEBUG
      for (int i = depth; i < g_max_depth; ++i) { cout << "\t"; }
      if (current_state.on_move() == white) {
        cout << "<" << depth << " " << "move-white " << next_move << ">";
      } else {
        cout << "<" << depth << " " << "move-black " << next_move << ">";
      } 
    #endif
//    if (clock() - start_time < MAX_TIME) {
      #ifdef DEBUG
        if (depth != 1) {
          cout << endl;
        }
      #endif
      value = max(value, -(negamax(current_state, depth - 1, start_time, states_evaluated, -beta, -alpha_0)));
      alpha_0 = max(alpha_0, value);
      current_state.unmake_move(next_move, captured);
      current_state.update_side_on_move();
      if (value >= beta) {
        best_move = next_move;
        return value;
      }
  //  } else {
      #ifdef DEBUG
   //     cout << value << " #out of time value" << endl;
      #endif
    //  best_move = next_move;
     // cout << "returning with " << best_move << endl;
      //return value;
    //}
  }
  #ifdef DEBUG
    bool move = potential_state.on_move();
    cout << endl;
    for (int i = depth; i < g_max_depth; ++i) { cout << "\t"; }
    cout << "Potential state before best move at this level: " << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Level: " << depth << endl;
    potential_state.print();
    cout << "------------------------------------------------" << endl;
    cout << endl;
    for (int i = depth; i < g_max_depth; ++i) { cout << "\t"; }
    if (move == white) { cout << "Best white score: "; }
    else { cout << "Best black score: "; }
    cout << value;
    cout << endl;
    for (int i = depth; i < g_max_depth; ++i) { cout << "\t"; }
    if (move == white) { cout << "Best white move: "; }
    else { cout << "Best black move: "; }
    cout << best_move;
    cout << endl << endl;
  #endif
  hash = current_state.get_hash();
  table_entry = new TTableEntry(hash, depth, alpha, beta, value);
  TTable::save_entry(*table_entry);
  best_move = next_move;
  return value;
}
