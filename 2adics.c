#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>

uint32_t gcd(uint32_t a, uint32_t b) {
    while (b != 0) {
        uint32_t r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int32_t twoadic(const int32_t A, const int32_t B) {
    int64_t x = 4611686018427387903; // Last 32 bits are 1’s
    while (x % B != 0 && x > 4294967295) {
        x++;
        x >>= 1;
        x--;
    }
    int64_t y = -x/B;
    return (int32_t) y*A;
}

int32_t valuation(const int32_t A) { // Exponent of the highest power of 2 that divides a
    uint32_t val = 0;
    while (fmod(A, exp2(val + 1)) == 0) val++;
    return val;
}

double twoabs(const int32_t A, const int32_t B) {
    if (A == 0) return 0;
    return 1/exp2(valuation(A) - valuation(B));
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: 2adics <a> <b>\n");
        return 1;
    }

    int32_t a = atol(argv[1]);
    int32_t b = atol(argv[2]);

    if (b == 0) {
        fprintf(stderr, "Can't divide by 0\n");
        return 1;
    }
    else {
        if (b < 0) {
            a *= -1;
            b *= -1;
        }
        int32_t d = gcd(abs(a), abs(b));
        a /= d;
        b /= d; // Reduce a/b to canonical form

        if (!(b & 1)) printf("%" PRId32 "/%" PRId32 " doesn't have a 2-adic representation", a, b); // If b is divisible by 2
        else {
            if (b == 1) printf("2-adic representation of %" PRId32 ": ...", a);
            else printf("2-adic representation of %" PRId32 "/%" PRId32 ": ...", a, b);
            int32_t adic = twoadic(a, b);
            for (int8_t i = 31; i >= 0; i--) putchar(((adic >> i) & 1) + 48); // 0 is ASCII character 48
        }
        
        if (b == 1) printf("\n2-adic absolute value of %" PRId32 " (in decimal): %g\n", a, twoabs(a, b));
        else printf("\n2-adic absolute value of %" PRId32 "/%" PRId32 " (in decimal): %g\n", a, b, twoabs(a, b));
    }

    return 0;
}
