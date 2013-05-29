Chesster

Chess bot for CS 442 with Bart Massey, Portland State University

Homework 2

In this part of the assignment I implemented a state evaluator and 
a negamax function. One of the challenges I came across this week
was that after negamax was implemented my bots would try to make
illegal moves. This was because my "best move" would be overwritten
upon recursive calls to negamax and would result in future possible
moves being tried. This was fixed by creating a local "best move"
for each iteration and then the value during the topmost recursive
call would be stored in a "final best move" variable before returning.

After fixing the illegal moves problem my bot still did not seem to be
making "good" moves, so I implemented some debugging printouts to help
monitor the state evaluation process.

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
