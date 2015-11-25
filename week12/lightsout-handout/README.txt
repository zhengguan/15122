15-122 Principles of Imperative Computation
Lights Out

==========================================================

Files you won't modify:
   lib/contracts.h     - Contracts for C
   lib/xalloc.{c,h}    - NULL-checking allocation
   lib/boardutil.{c,h} - Useful Lights-Out relevant functions
   lib/hset.{c,h}      - Hash sets
   lib/stacks.{c,h}    - Stacks
   lib/queues.{c,h}    - Queues
   lib/bitarray.h      - Interface to bit arrays
   lib/ba-ht.h         - Interface to bit array hashtables
   Makefile            - Utility for building this project

Files that don't exist yet:
   bitarray.c          - Bit array implementation
   bitarray-test.c     - Your unit tests for bit arrays (Optional)
   ba-ht.c             - Bit array hashtable wrapper implementation
   lightsout.c         - Lights out implementation (needs a main() function)

==========================================================

Compiling your bitarray unit tests
   % make bitarray-test
   % ./bitarray-test

Compiling and running your lights out solver (with -DDEBUG)
   % make
   % ./lightsout-d boards/board0.txt

Compiling and running your lights out solver (without -DDEBUG)
   % make
   % ./lightsout boards/board0.txt 

==========================================================

Submitting with Andrew handin script:
   % handin lightsout lightsout.c ba-ht.c bitarray.c

Creating a tarball to submit with Autolab web interface:
   % tar -czvf lightsoutsol.tgz lightsout.c ba-ht.c bitarray.c

On autolab: https://autolab.cs.cmu.edu/15122-f14/lightsout


