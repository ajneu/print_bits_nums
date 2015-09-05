# print_bits_nums
C function-like macro to print numbers according to their type.

## The problem (in C)

C++ can do this:
```cpp
std::cout << (-1+0U) << std::endl;
```

But how do you do this in C, if you don't want to give `printf` clues in the form of specifiers such as e.g. `%u`
```c
printf("%u", (-1+0U));
```
???

### Or formulated as a *Challenge!*

*Challenge!!*  
Given an string-buffer: `char s[129];`  
write a function-like macro `sprint_num(s, num)` in standard C  
that prints the number `num` into the string-buffer `s`

It should behave as follows:
```cpp
    sprint_num(s, 1);
    puts(s);   // should print: 1
    sprint_num(s, 255U);
    puts(s);   // should print: 255    
    sprint_num(s, 65535U);
    puts(s);   // should print: 65535
    sprint_num(s, 4294967295UL);
    puts(s);   // should print: 4294967295
    sprint_num(s, 18446744073709551615ULL);
    puts(s);   // should print: 18446744073709551615

    sprint_num(s, -1);
    puts(s);   // should print: -1
    sprint_num(s, -128);
    puts(s);   // should print: -128
    sprint_num(s, -32768);
    puts(s);   // should print: -32768
    sprint_num(s, -2147483647L - 1);
    puts(s);   // should print: -2147483648
    sprint_num(s, -9223372036854775807LL-1);
    puts(s);   // should print: -9223372036854775808

```

**Can you write the function-like macro `sprint_num`???** (You're welcome to try writing it as a normal (non-macro) function, but actually that's impossible when using standard C.)  
While you're at it, try writing `sprint_bin`, `sprint_hex`, and `sprint_oct` as well

## A possible solution

Use a modern language such as C++.

**How to do it in standard C? See [c_example](https://github.com/ajneu/print_bits_nums/tree/master/c_example)!**  
-> uses a function-like macro in C  
and makes use of a few nifty macros 
* from the [P99 project](http://p99.gforge.inria.fr/) (by [Jens Gustedt](https://gustedt.wordpress.com/))  
used [here](https://github.com/ajneu/print_bits_nums/blob/master/c_example/include/print_bits.h#L7)
* and from the `type-props.h` header [1](http://yuba.stanford.edu/git/gitweb.cgi?p=openflow.git;a=commit;h=fd90251602dd04eb3a954b1eda790e781b03d9f8) [2](https://github.com/noxrepo/openflow/blob/master/lib/type-props.h) [3](https://github.com/openvswitch/ovs/blob/master/lib/type-props.h) (by [Ben Pfaff](http://benpfaff.org/))

Basically:

```c
#include <stdio.h>

/* http://p99.gforge.inria.fr/p99-html/group__integers_ga3eb39ccac28ebd8265c1a31dc00f53ab.html 

   P99 homepage: http://p99.gforge.inria.fr/
   P99 repo:     https://scm.gforge.inria.fr/anonscm/gitweb?p=p99/p99.git;a=tree
*/
#define P99_SIGN_PROMOTE(A, B) (1 ? (A) : (B))
#define P99_PROMOTE_0(EXPR)    P99_SIGN_PROMOTE(0, (EXPR))
#define P99_PROMOTE_M1(EXPR)   P99_SIGN_PROMOTE(-1, (EXPR))
#define P99_SIGNED(EXPR)      (P99_PROMOTE_M1(EXPR) < P99_PROMOTE_0(EXPR))

#define BUFLEN_PRINTBITS ((sizeof(unsigned long long) * CHAR_BIT) + 1) /* 65 */

#define sprint_num(s, x) (P99_SIGNED(x)                                     \
                          ? sprintf(s, "%lld", (  signed long long)(x))     \
                          : sprintf(s, "%llu", (unsigned long long)(x)))
```

## Addition

If you like to print numbers to string-buffers, without pulling in `stdio.h`, have a look at
* [`void sprint_signed(char *s, long long num)`](https://github.com/ajneu/print_bits_nums/blob/master/c_example/src/print_bits.c#L70)
* [`void sprint_unsigned(char *s, unsigned long long num)`](https://github.com/ajneu/print_bits_nums/blob/master/c_example/src/print_bits.c#L81)
