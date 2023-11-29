#include <stdio.h>
#include <math.h>

int gcd(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return abs(a);
}

int twoadic(int a, int b) {
    long long x = 4611686018427387903; // Last 32 bits are 1’s
    while (x % b != 0 && x > 4294967295) {
        x++;
        x >>= 1;
        x--;
    }
    long long y = -x/b;
    return (int) y*a;
}

void printbin(int a) {
    for (int i = sizeof(a)*8 - 1; i >= 0; i--) putchar(((a >> i) & 1) + 48); // 0 is ASCII character 48
}

int valuation(int a) { // Exponent of the highest power of 2 that divides a
    int val = 0;
    while (fmod(a, exp2(val + 1)) == 0) val++;
    return val;
}

double twoabs(int a, int b) {
    if (a == 0) return 0;
    return 1/exp2(valuation(a) - valuation(b));
}

int main(void) {
    int a, b;
    char c;

    do {
        printf("\nEnter the numerator: ");
        scanf("%d", &a);
        printf("Enter the denominator (1 for integer): ");
        scanf("%d", &b);

        if (b == 0) printf("Can't divide by 0");
        else {
            if (b < 0) {
                a *= -1;
                b *= -1;
            }
            int d = gcd(a, b);
            a /= d;
            b /= d; // Reduce a/b to canonical form

            if (b % 2 == 0) printf("%d/%d doesn't have a 2-adic representation", a, b);
            else {
                if (b == 1) printf("2-adic representation of %d: ...", a);
                else printf("2-adic representation of %d/%d: ...", a, b);
                printbin(twoadic(a, b));
            }
            
            if (b == 1) printf("\n2-adic absolute value of %d (in decimal): %g", a, twoabs(a, b));
            else printf("\n2-adic absolute value of %d/%d (in decimal): %g", a, b, twoabs(a, b));
        }
        printf("\nContinue? (y/n) ");
        scanf("%s", &c);
    } while (c == 'y' || c == 'Y');

    return 0;
}
