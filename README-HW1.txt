Chesster

Chess bot for CS 442 with Bart Massey, Portland State University

Homework 1

I wrote this assignment in C++. It is the language I am most comfortable in and
I felt that a low-level language like C++ would allow me the control to design 
a fast program. C++ can be object-oriented, and the assignment seems to call 
for an object-oriented design.

I used a two-dimensional array of characters to represent the chess board. This
seems to be the easiest to implement. I thought that using a one-dimensional 
array and implementing the arithmetic to move across rows would not have any 
real performance gain over letting C++ implement the exact same thing itself.
I did not use a bitboard because the programmatic hassle of implementing it
and the probable resulting unreadability of the code would not be worth a
modest gain in performance.

I used C++ STL vectors to represent the lists of moves. This data structure
was much more convenient and well-suited to this use than any data structure 
I could implement would have been. I didn't use an STL list because I wanted
to be able to randomly access an element. There didn't seem to be an easy
way to add a vector to the end of another vector, however, so I implemented
a global function that adds elements from one vector one by one to the other
vector.
