#ifndef PRINT_BITS_H
#define PRINT_BITS_H

#include <limits.h> /* CHAR_BIT */


/* http://p99.gforge.inria.fr/p99-html/group__integers_ga3eb39ccac28ebd8265c1a31dc00f53ab.html */
#define P99_SIGN_PROMOTE(A, B) (1 ? (A) : (B))
#define P99_PROMOTE_0(EXPR) P99_SIGN_PROMOTE(0, (EXPR))
#define P99_PROMOTE_M1(EXPR) P99_SIGN_PROMOTE(-1, (EXPR))
#define P99_SIGNED(EXPR) (P99_PROMOTE_M1(EXPR) < P99_PROMOTE_0(EXPR))

#define BUFLEN_PRINTBITS ((sizeof(unsigned long long) * CHAR_BIT) + 1) /* 65 */


/*************
PRINT BIT PATTERN
sprint_bits(char* buffer, number)
**************/
void print_bits_func(char *s, unsigned long long bit_mover, unsigned long long x);

/* #define EXPR_MSB(EXPR) (~(~(unsigned long long)0 << (sizeof(EXPR) * CHAR_BIT - 1)) + 1) */
#define EXPR_MSB(EXPR) ((unsigned long long)1 << (sizeof(EXPR) * CHAR_BIT - 1))
#define sprint_bits(s, x) print_bits_func(s, EXPR_MSB(x), x)



/*************
PRINT HEX PATTERN
sprint_hex(char* buffer, number)
**************/
void print_hex_func(char *s, int offs, unsigned long long x);

#define EXPR_4_OFFSET(EXPR) ((sizeof(EXPR) * CHAR_BIT - 1) / 4 * 4)
#define sprint_hex(s, x) print_hex_func(s, EXPR_4_OFFSET(x), x)



/*************
PRINT OCT PATTERN
sprint_oct(char* buffer, number)

Careful: this function prints ONLY the bits of the specific width and DOES NOT DO SIGN-EXTENSION

So: sprint_oct(char* buffer, (char -1))
yieds s pointing to "377" and not "777"
**************/
void print_oct_func(char *s, int offs, unsigned long long x);

#define MASK_WIDTH(EXPR) (~0ULL >> ((sizeof(0ULL)-sizeof(EXPR)) * CHAR_BIT)) /*(~(~0ULL << (sizeof(x) * CHAR_BIT)))*/  
#define EXPR_3_OFFSET(EXPR) ((sizeof(EXPR) * CHAR_BIT - 1) / 3 * 3)
#define sprint_oct(s, x) print_oct_func(s, EXPR_3_OFFSET(x), x & MASK_WIDTH(x))



/*************
PRINT NUMBER
sprint_num(char* buffer, number)
**************/
void sprint_signed(char *s, long long num);
void sprint_unsigned(char *s, unsigned long long num);

#define sprint_num(s, x) (P99_SIGNED(x) ? sprint_signed(s, x) : sprint_unsigned(s, x))



#endif
