#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>

#define UINT_HALF uint32_t // uint16_t
#define INT_TYPE int64_t // int32_t
#define INT_HALF int32_t // int16_t
#define INT_HALF_PRINT PRId32 // PRId16
#define FLOAT_TYPE double // float
#define UINT_HALF_MAX UINT32_MAX // UINT16_MAX
#define EXP2 exp2 // exp2f

UINT_HALF gcd(UINT_HALF a, UINT_HALF b)
{
	while (b != 0) {
		UINT_HALF r = a % b;
		a = b;
		b = r;
	}
	return a;
}

INT_HALF twoadic(const INT_HALF A, const INT_HALF B)
{
	INT_TYPE x = 0x3fffffffffffffff; // Last 32 bits are 1’s
	while (x % B != 0 && x > UINT_HALF_MAX) {
		x++;
		x >>= 1;
		x--;
	}
	INT_TYPE y = -x/B;
	return (INT_HALF)y*A;
}

INT_HALF valuation(const INT_HALF A)
{ // Exponent of the highest power of 2 that divides a
	UINT_HALF val = 0;
	while (fmod(A, EXP2(val + 1)) == 0)
		val++;
	return val;
}

FLOAT_TYPE twoabs(const INT_HALF A, const INT_HALF B)
{
	if (A == 0)
		return 0;
	return 1/EXP2(valuation(A) - valuation(B));
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		fprintf(stderr, "Usage: 2adics <a> <b>\n");
		exit(EXIT_FAILURE);
	}

	INT_HALF a = atol(argv[1]);
	INT_HALF b = atol(argv[2]);

	if (b == 0) {
		fprintf(stderr, "Error: can't divide by 0\n");
		exit(EXIT_FAILURE);
	} else {
		if (b < 0) {
			a *= -1;
			b *= -1;
		}
		INT_HALF d = gcd(abs(a), abs(b));
		a /= d;
		b /= d; // Reduce a/b to canonical form

		if (!(b & 1)) {
			printf("%" PRId32 "/%" PRId32 " doesn't have a 2-adic representation", a, b); // If b is divisible by 2
		} else {
			if (b == 1)
				printf("2-adic representation of %" PRId32 ": ...", a);
			else
				printf("2-adic representation of %" PRId32 "/%" PRId32 ": ...", a, b);
			const INT_HALF ADIC = twoadic(a, b);
			for (uint8_t i = 32; i > 0; i--)
				putchar(((ADIC >> (i - 1)) & 1) + 48); // 0 is ASCII character 48
		}

		if (b == 1)
			printf("\n2-adic absolute value of %" PRId32 " (in decimal): %g\n", a, twoabs(a, b));
		else
			printf("\n2-adic absolute value of %" PRId32 "/%" PRId32 " (in decimal): %g\n", a, b, twoabs(a, b));
	}

	exit(EXIT_SUCCESS);
}
