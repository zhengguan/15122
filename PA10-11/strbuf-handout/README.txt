15-122 Principles of Imperative Computation
String Buffers

==========================================================

Files you won't modify:
   lib/cstring.c0  - C0 implementation of some of the C string.h library
   cstring-test.c0 - Some unit tests for the cstring library
   strbuf.h        - Interface to string buffers
   lib/contracts.h - Contracts for C 
   lib/xalloc.h    - Interface of NULL-checking allocation
   lib/xalloc.c    - Implementation of NULL-checking allocation

   Include the contracts and xalloc library interfaces in your C code
   by writing:
   #include "lib/contracts.h"
   #include "lib/xalloc.h"

Code to fill in:
   strbuf.c0 - Implementation of string buffers (C0)

Files that don't exist yet:
   strbuf.c       - Implementation of string buffers (C)
   strbuf-test.c0 - Testing for strbuf.c0
   strbuf-test.c  - Testing for strbuf.c (Optional, highly recommended)

==========================================================

Compiling C0 code with contracts:
   % cc0 -d -w lib/*.c0 strbuf.c0 strbuf-test.c0
   % ./a.out

Compiling C0 code without contracts:
   % cc0 -w lib/*.c0 strbuf.c0 strbuf-test.c0
   % ./a.out

Compiling C code with contracts:
   % gcc -DDEBUG -g -Wall -Wextra -Werror -std=c99 -pedantic lib/*.c strbuf.c strbuf-test.c
   % ./a.out

Compiling C code without contracts:
   % gcc -Wall -Wextra -Werror -std=c99 -pedantic lib/*.c strbuf.c strbuf-test.c
   % ./a.out

==========================================================

Submitting with Andrew handin script:
   % handin strbuf strbuf.c strbuf.c0 strbuf-test.c strbuf-test.c0

Creating a tarball to submit with Autolab web interface:
   % tar -czvf strbufsol.tgz strbuf.c strbuf.c0 strbuf-test.c strbuf-test.c0

On autolab: https://autolab.cs.cmu.edu/15122-f14/strbuf
