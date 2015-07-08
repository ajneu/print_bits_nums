# print_bits_nums
C function-like macro to print numbers according to their type.

## The problem (in C)

C++ can do this:
```
std::cout << (-1+0U) << std::endl;
```

But how do you do this in C, if you don't want to give `printf` clues in the form of specifiers such as e.g. `%u`
```
printf("%u", (-1+0U));
```
???

## A solution

Use a modern language such as C++.  
Or: hack out a function-like macro in C to do it 
(and also use a few nifty macros from the [P99 project](http://p99.gforge.inria.fr/))
