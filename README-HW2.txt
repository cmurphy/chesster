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
