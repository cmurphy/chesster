Chesster

Chess bot for CS 442 with Bart Massey, Portland State University

Homework 3

I tried to implement iterative deepening that would interrupt negamax
in order to try to keep accurate time. This introduced a bug whereby
negamax would return a move chosen from the middle of the list of states
since it ran out of time to evaluate every state at that depth. I 
corrected this by removing the interrupting timers and instead keeping
time with a single while loop around the negamax call. The problem
with this is that if negamax returns just under the allotted time,
the program will execute negamax again and end up going way over
the allotted time. Still, it now makes good moves and accurate timing
can be implemented later.

Before implementing alpha-beta pruning, negamax would evaluate between
200,000 and 1,700,000 states taking up to 21 seconds (which is approximately
entirely alloted to evaluating at the last depth). It would reach 5-6 levels
deep.

After implementing alpha-beta pruning, it still only evaluates 5-6 levels,
but not only evaluates 50,000 to 200,000 states and only takes 1-7 seconds.

Implementing do-undo (after alpha-beta) did not significantly affect the 
number of states evaluated nor the depth of evaluation. There is some
debate online around whether do-undo offers significant improvement 
when implemented in a relatively low-level language like C++ and in which
the datastructure representing the board is not very complex. A 5x6 char
array is not very complex for C++ to manipulate. If this had been implemented
with a bit board do-undo would probably cause even more overhead and 
be detrimental to performance.

In the interest of time and since my bot already plays admirably I only
made slight adjustments to the state evaluation. It favors moving the 
knight, rook, and bishop out of the home row and keeping the king 
in the home row. Since implementing do-undo these evaluations now take
place in make_move and unmake_move instead of in the evaluate function.
I added a new evaluate function that simply returns the state's saved
score and will deprecate the old evaluation once everythign else is 
completed.
