#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>

int32_t gcd(int32_t a, int32_t b) {
    while (b != 0) {
        int32_t r = a % b;
        a = b;
        b = r;
    }
    return abs(a);
}

int32_t twoadic(int32_t a, int32_t b) {
    int64_t x = 4611686018427387903; // Last 32 bits are 1’s
    while (x % b != 0 && x > 4294967295) {
        x++;
        x >>= 1;
        x--;
    }
    long long y = -x/b;
    return (int32_t) y*a;
}

void printbin(int32_t a) {
    for (int8_t i = 31; i >= 0; i--) putchar(((a >> i) & 1) + 48); // 0 is ASCII character 48
}

int32_t valuation(int32_t a) { // Exponent of the highest power of 2 that divides a
    int32_t val = 0;
    while (fmod(a, exp2(val + 1)) == 0) val++;
    return val;
}

double twoabs(int32_t a, int32_t b) {
    if (a == 0) return 0;
    return 1/exp2(valuation(a) - valuation(b));
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: 2adics <a> <b>\n");
        return 1;
    }

    int32_t a = atoi(argv[1]);
    int32_t b = atoi(argv[2]);

    if (b == 0) {
        fprintf(stderr, "Can't divide by 0\n");
        return 1;
    }
    else {
        if (b < 0) {
            a *= -1;
            b *= -1;
        }
        int32_t d = gcd(a, b);
        a /= d;
        b /= d; // Reduce a/b to canonical form

        if (b % 2 == 0) printf("%" PRId32 "/%" PRId32 " doesn't have a 2-adic representation", a, b);
        else {
            if (b == 1) printf("2-adic representation of %" PRId32 ": ...", a);
            else printf("2-adic representation of %" PRId32 "/%" PRId32 ": ...", a, b);
            printbin(twoadic(a, b));
        }
        
        if (b == 1) printf("\n2-adic absolute value of %" PRId32 " (in decimal): %g\n", a, twoabs(a, b));
        else printf("\n2-adic absolute value of %" PRId32 "/%" PRId32 " (in decimal): %g\n", a, b, twoabs(a, b));
    }

    return 0;
}
