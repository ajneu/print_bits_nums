#include "print_bits.h"
#include "type-props.h"

#if __STDC_VERSION__ < 201112L
/* not C11 */
#include "static_assert.h"
#endif

/*************
PRINT BIT PATTERN
sprint_bits(char* buffer, number)
**************/
void print_bits_func(char *s, unsigned long long bit_mover, unsigned long long x)
{
    for (; bit_mover; s++, bit_mover >>= 1)
      *s = '0' + ((bit_mover & x) != 0); /* *s = '0' + ((bit_mover & x) ? 1 : 0) */
    *s = '\0';
}



/*************
PRINT HEX PATTERN
sprint_hex(char* buffer, number)
**************/
void print_hex_func(char *s, int offs, unsigned long long x)
{
    static char hex_digs[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    for (; offs >= 0; s++, offs-=4)
        *s = hex_digs[(x >> offs) & 0xF];
    *s = '\0';
}



/*************
PRINT OCT PATTERN
sprint_oct(char* buffer, number)

Careful: this function prints ONLY the bits of the specific width and DOES NOT DO SIGN-EXTENSION

So: sprint_oct(char* buffer, (char -1))
yieds s pointing to "377" and not "777"
**************/
void print_oct_func(char *s, int offs, unsigned long long x)
{
    for (; offs >= 0; s++, offs-=3)
        *s = '0' + ((x >> offs) & 0x7);
    *s = '\0';
}




#define BASE10_64BITS 10000000000000000000ULL
#define BASE10_32BITS 1000000000U

#if __STDC_VERSION__ >= 201112L
/* C11 */
_Static_assert(((TYPE_MAXIMUM(unsigned long long)/10) <  BASE10_64BITS) && (BASE10_64BITS <= TYPE_MAXIMUM(unsigned long long)), "check_base10_64bits");
_Static_assert(((TYPE_MAXIMUM(int)/10) <  BASE10_32BITS) && (BASE10_32BITS <= TYPE_MAXIMUM(int)), "check_base10_32bits");
#else
STATIC_ASSERT(((TYPE_MAXIMUM(unsigned long long)/10) <  BASE10_64BITS) && (BASE10_64BITS <= TYPE_MAXIMUM(unsigned long long)), check_base10_64bits);
STATIC_ASSERT(((TYPE_MAXIMUM(int)/10) <  BASE10_32BITS) && (BASE10_32BITS <= TYPE_MAXIMUM(int)), check_base10_32bits);
#endif




void sprint_signed(char *s, long long num)
{
    /* what this function does: sprintf(s, "%lld", num); */
    
    if (num < 0LL) {
        *s++ = '-';
        num = -num;
    }
    sprint_unsigned(s, num);
}

void sprint_unsigned(char *s, unsigned long long num)
{
    /* what this function does: sprintf(s, "%llu", num); */

    unsigned long long fac10;
    if (! num) {
        s[0] = '0';
        s[1] = '\0';
        return;
    }

    fac10 = (0xFFFFFFFF00000000ULL & num) ? BASE10_64BITS : BASE10_32BITS;
    for ( ; ! (num / fac10); fac10 /= 10)
        ;
    *s++ = '0' + (num / fac10);

#define SPRINT_UNSIGNED_VARIANT 1

#if (SPRINT_UNSIGNED_VARIANT==1)
    /* variant 1 */
    num = num % fac10;
    {
        while (fac10 /= 10) {
            *s++ = '0' + (num / fac10);
            num = num % fac10;
        }
    }

#elif (SPRINT_UNSIGNED_VARIANT==2)

    /* variant 2 */
    num = num % fac10;
    while (fac10 /= 10) {
        register unsigned long long tmp;
        *s++ = '0' + (tmp = (num / fac10));
        num = num - tmp * fac10; // num = num % fac10;
    }

#else

    /* variant 3 */
    {
        register unsigned long long fac10_tmp;
        while (fac10 = (fac10_tmp = fac10) / 10) {
            num = num % fac10_tmp;            
            *s++ = '0' + (num / fac10);
        }
    }

#endif

    *s = '\0';
}



#if 1
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char s[BUFLEN_PRINTBITS];
    char x=15;

    fputs("Binary: ", stdout);
    puts( (sprint_bits(s, x), s) );
    /*                       \
                        comma operator */

    fputs("Hex   : ", stdout);
    puts( (sprint_hex(s, x), s) );
    /*                      \
                       comma operator */

    fputs("Oct   : ", stdout);
    puts( (sprint_oct(s, x), s) );
    /*                      \
                       comma operator */




    fputs("Binary: ", stdout);
    puts( (sprint_bits(s, -1+11), s) );
    /*                           \
                           comma operator */

    fputs("Hex   : ", stdout);
    puts( (sprint_hex(s, -1+11), s) );
    /*                          \
                           comma operator */

    fputs("Oct   : ", stdout);
    puts( (sprint_oct(s, -1+11), s) );
    /*                          \
                           comma operator */



    unsigned long long ull = 0x8000000000000000;
    fputs("Unsigned number : ", stdout);
    puts( (sprint_num(s, ull), s) );

    signed long long sll = 0x8000000000000000;
    fputs("Signed number   : ", stdout);
    puts( (sprint_num(s, sll), s) );

    fputs("understanding integer promotion: -2+0U = ", stdout);
    puts( (sprint_num(s, -2+0U), s) ); /* note the integer promotion of -1 to unsigned, according to the promotion rules! */

    return EXIT_SUCCESS;
}
#endif
