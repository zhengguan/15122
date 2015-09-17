15-122 Principles of Imperative Computation
Doslingos

Files you won't modify:
   lib/arr_lib.c0       - Helper functions for esaily creating test arrays
   lib/arrayutil.c0     - A version of arrayutil.c0 for strings
   lib/readfile.c0      - File reading library (Part 2, page 4)
   lib/stringsearch.c0  - String searching library (Part 2, pages 4-5)
   doslingos-awful.c0   - Badly broken implementation
   echo.c0              - Example of using the C0 args library

Files that don't exist yet:
   doslingos.c0         - Code for tasks 1 and 2
   doslingos-test.c0    - Testing doslingos.c0
   analysis.c0          - Using the DosLingos code to answer questions

Data: (described on page 4 of the handout)
   texts/news_vocab_sorted.txt 
   texts/scott_tweet.txt
   texts/sonnets.txt
   texts/shakespeare.txt

   You can create more data files if you would like to use them in
   your tests: just hand these in along with your other files.

==========================================================

Loading all the libraries in coin to play with them:
   % coin lib/*.c0
 
Compiling doslingos.c0 and tests:
   % cc0 -d -w -o doslingos lib/*.c0 doslingos.c0 doslingos-test.c0
   % ./doslingos 
   
Compiling doslingos.c0 and tests:
   % cc0 -d -w -o doslingos-bad lib/*.c0 doslingos-awful.c0 doslingos-test.c0
   % ./doslingos-bad
   
Compiling analysis.c0:
   % cc0 -w -o analysis lib/*.c0 doslingos.c0 analysis.c0
   % ./analysis texts/news_vocab_sorted.txt texts/shakespeare.txt

==========================================================

Submitting with Andrew handin script:
   % handin doslingos doslingos.c0 doslingos-test.c0 analysis.c0

Creating a tarball to submit with autolab.cs.cmu.edu web interface:
   % tar -czvf doshandin.tgz doslingos.c0 doslingos-test.c0 analysis.c0
