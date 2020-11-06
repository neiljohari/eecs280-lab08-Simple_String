# EECS 280 SimpleString Example

_Note:_ This repository is **not** solution code for Lab08. This is a documented
solution for a practice problem shown during my EECS280 lab section for Lab08.

This is a good example of how to use the Big 3 to effectively create your own
lightweight version of std::string. It is not nearly as efficient (doesn't take
advantage of c++11 move semantics), but it is a great example tying together
many concepts like C-Style strings, dynamically allocated memory, `delete` vs
`delete[]`, copy ctor, assignment operator, default parameters, etc.

I encourage you to play around in `main.cpp`. I provided a Makefile so it should
be as easy as running `make` to compile the code (the executable will, by
default, be called `solution`).
