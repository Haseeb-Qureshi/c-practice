# C Programming language

## Macros
  * Before compilation, this is preprocessed and code is expanded
  * #include
    * Loads a header file
  * #define MAX(x, y) x > y ? x : y
    * Problem with macros—they do not parenthesize the code the way that a function call would.
    * Need to manually parenthesize things yourself, both when defining macros and when using macros
  * Two types of files in C:
    * `.h`
      * Where your declarations go
    * `.c`
      * Where your definitions go
      * Where your code goes
    * #include `<stdio.h>` brackets means it's a system library
      * It exposes `printf(str)`
      * Stdio.h declares a function that you're going to use, but does not define it.
    * Compiles to `.o` files which are "object files"

## Linking
  * GCC `gcc -o main main.o somethingelse.o` does LINKING which combines different object files so that they all do the same thing.

## Compilation
  * `gcc -o output_filename filename.c`

## printf
  * Only flushes buffer if you print a `\n` or if you call `fsync`.
  * Can also manually change these flush settings.
  * Context switch of flushing buffer is expensive.
  * If your program terminates early, it is guaranteed that the buffer will be flushed.
  * If a program is interrupted, then it won't necessarily flush its buffer.

## Flags
  * `-std C99` — if you compile with this flag, this is the ISO standard for C code
  * `C11`, `ANSI`
  * By default uses ANSI

## gcc
  * GNU C compiler
  * Also `clang`, is supposed to be interchangeable with `gcc`. OSX uses `clang` because they don't like the licensing of `gcc`. Also aliased as `bin/gcc`

## data types
  * `char` as the `byte` data type
  * Other data types:
    * `int`
    * `long`
    * `double`
    * `float`
    * `short`
    * `long double`

## reading I/O
  * `gets` and `fgets`
    * `fgets` takes the buffer, and the amount to read into the buffer.
  * Never ever use `gets`, because it will read as many bytes as the user gives you.
  * No `string` data type in C
  * There is a data type called `char`, that's it.
  * You have to allocate an array of `char`s.
  * Usually called `buf` as `char buf[255]`.
  * Can do `buf[0] = 'A'`
  * `buf[1] = 0`
    * String terminator
  * Can do `printf("%s\n", buf)`

## strings
  * Only string literals
    * Compiler allocates space in the program (the data segment, which is read-only), and "abc" becomes a `char*` for that space in the data segment.
    * String literals are *read-only*, if you modify it your program will get killed for modifying read-only memory.

## enums
  * Enums are always integers
  * If you create two, first will be 0, second will be 1.
  * If you want to set their values, you can say:
    * ` { BELL = '\a', BACKSPACE = '\b', etc. };`

## errors
  * C has no native error handling
  * `int* result = func();`
  * result is logically, always non-negative
  * You can say `if (result == 0)` wtf? Null pointer.
  * There's a global variable called `int ERRNO` which is defined in `errno.c`, also `errno.h`
  * `#include <errno.h>`
  * `printf("%d\n", errno);`
  * `static int errno;`

## pointers
  * Two operators in C
  * * (dereferencer)
    * `int* buf;` pointer to characters
    * `buf = malloc(255 * sizeof(int))`
    * malloc returns `void*` => a pointer to "IDK"
      * `void* x;`
      * `printf("%lu", x);`
    * `buf = (int*) malloc(255 * sizeof(int));`
  * `buf[0] = 0; buf[1] = 1;`
  * `*buf = 0;`
  * `*(buf + 1) = 0;`
  * `*buf = *(buf + 1)`

## pass-by-value
  * everything in C is pass-by-value
  * if you want to use pass-by-reference, you need to say `void square(int* yp) { *yp = (*yp) * (*yp); }`
  * In order to call this, you have to say `int x = 5; square(&x);`
  * Ampersand is used to go from a value to a pointer
  * Star is used to go from a pointer to its value
  * `char* buf` == `char buf2[]`
  * `char* buf = malloc(255);` == `char buf2[255];`
  * `buf[3] == *(buf2 + 3);`
