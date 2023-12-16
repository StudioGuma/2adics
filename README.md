Command line program that calculates & prints the last 32 digits of the representation of a rational number as a 2-adic integer, as well as its 2-adic absolute value. Takes 2 integer inputs, the numerator a & the denominator b, to make the rational number a/b.

[Watch this](https://www.youtube.com/watch?v=tRaq4aYPzCc) if you don’t know what p-adics are, but basically, it’s a way of writing a rational number in base p with infinitely many digits, which works best if p is a prime number. For every p^n, the higher n is, the closer to 0 the absolute value is.

Works for any a & b between -2147483648 & 2147483647 inclusive (except where b = 0), but a/b will be reduced to canonical form (a & b are coprime; b > 0). Every a/b has a 2-adic expansion so long as b isn’t divisible by 2, tested to be accurate for smaller denominators. For integers (i.e. for b = 1), it’s conveniently the same as two’s complement.

Building requires installing a compiler, preferably GCC, and Make on Windows. To build, open a command line & type `make`. You can then execute by typing `2adics <a> <b>` (on Windows) or `./2adics <a> <b>` (on Unix-like systems), where `<a>` and `<b>` are the numerator & denominator inputs, and clean by typing `make clean` after editing the makefile based on your OS.

Executable size: 248 KB
