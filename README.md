# 2adics

Command line program written in C that calculates and prints the last 32 digits of the representation of a rational number as a 2-adic integer, as well as its 2-adic absolute value. Takes 2 integer inputs, the numerator a and the denominator b, to make the rational number a/b.

[Watch this](https://www.youtube.com/watch?v=tRaq4aYPzCc) if you don’t know what p-adics are, but basically, it’s a way of writing a rational number in base p with infinitely many digits, which works best if p is a prime number. For every p^n, the higher n is, the closer to 0 the absolute value is.

Works for any a and b between -2147483648 and 2147483647 inclusive (except where b = 0), but a/b will be reduced to canonical form (a and b are coprime; b > 0). Every a/b has a 2-adic expansion so long as b is odd, tested to be accurate for smaller denominators. For integers (i.e. for b = 1), it’s conveniently the same as two’s complement.

Building requires a compiler, preferably GCC, and Make. Make sure to edit the makefile according to your compiler and OS. To build, open a command line and type `make`. You can then execute by typing `./2adics <a> <b>` (on Unix-like systems) or `2adics <a> <b>` (on Windows), where `<a>` and `<b>` are the numerator and denominator inputs, and clean by typing `make clean`.

Built for 64-bit systems by default, but you can edit the macros to change it to 32-bit.

Linux executable size: 16.4 kB
