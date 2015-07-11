#if __STDC_VERSION__ < 201112L
/* not C11 */
#error "you need a compiler that can handle C11 (reason: _Generic)"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BUFLEN_PRINTBITS ((sizeof(unsigned long long) * CHAR_BIT) + 1) /* 65 */


// http://www.robertgamble.net/2012/01/c11-generic-selections.html   -- see section "Printing values generically"
#define printf_dec_format(x) _Generic((x),                            \
                                      char: "%c",                     \
                                      signed char: "%hhd",            \
                                      unsigned char: "%hhu",          \
                                      signed short: "%hd",            \
                                      unsigned short: "%hu",          \
                                      signed int: "%d",               \
                                      unsigned int: "%u",             \
                                      long int: "%ld",                \
                                      unsigned long int: "%lu",       \
                                      long long int: "%lld",          \
                                      unsigned long long int: "%llu", \
                                      float: "%f",                    \
                                      double: "%f",                   \
                                      long double: "%Lf",             \
                                      char *: "%s",                   \
                                      void *: "%p")

#define sprint(s, x) sprintf((s), printf_dec_format(x), x)

int main(void)
{
    char s[BUFLEN_PRINTBITS];
    char x=15;

    fputs("Unsigned number : ", stdout);
    puts( (sprint(s, 1U), s) );

    fputs("Signed number   : ", stdout);
    puts( (sprint(s, -1), s) );

    unsigned long long ull = 0x8000000000000000;
    fputs("Unsigned number : ", stdout);
    puts( (sprint(s, ull), s) );

    signed long long sll = 0x8000000000000000;
    fputs("Signed number   : ", stdout);
    puts( (sprint(s, sll), s) );

    fputs("understanding integer promotion: -2+0U = ", stdout);
    puts( (sprint(s, -2+0U), s) ); /* note the integer promotion of -1 to unsigned, according to the promotion rules! */

    return EXIT_SUCCESS;
}
