15-122 Principles of Imperative Computation
Clac

Files you won't modify:
   lib/stack_of_int.c0             - Stacks containing integers
   lib/queue_of_string.c0          - Queues containing strings
   lib/stack_of_queue_of_string.c0 - Stacks containing queues of strings
   lib/tokenize.c0                 - Library for populating queues of strings
   clac-main.c0                    - Runs clac read-eval-print loop (REPL)

Files you will modify:
   clac.c0               - Clac interpreter
   clac-test.c0          - Testing the clac implementation (Optional)

Data:
   def/demo-fail.clac    - An example program that should call to error()
   def/demo-print.clac   - An example program that should print things out
   def/square.clac       - Squaring numbers
   def/sum.clac          - Summing a series of numbers
   def/fact.clac         - Factorial, with some Clac unit tests
   def/fib.clac          - Fibonacci example from the writeup
   def/fibalt.clac       - Another way of implementing fibonacci

==========================================================

The code that you're given will already compile and pass the given
tests in clac-test.c0.

Running the reference implementation of the Claculator (Andrew Linux only):
   % clac-ref def/demo-print.clac
   % clac-ref -trace
   clac>> 8 5 4 - + dup
   clac>> print print
   clac>> quit

Compiling and running the Claculator:
   % cc0 -d -w -o clac lib/*.c0 dict.c0 clac.c0 clac-main.c0
   % ./clac
   % ./clac def/demo-print.clac

Testing your Clac implementation:
   % cc0 -d -w -o clac-test lib/*.c0 dict.c0 clac.c0 clac-test.c0
   % ./clac-test
   % ./clac-test err1
   % ./clac-test err2
   % ./clac-test err3     # These two tests highlight a bug...
   % ./clac-test err4     # ...in the code you were given
   ...

==========================================================

Submitting with Andrew handin script:
   % handin clac clac.c0 dict.c0 bonus.clac

Creating a tarball to submit with Autolab web interface:
   % tar -czvf clachandin.tgz clac.c0 dict.c0 bonus.clac

On autolab: https://autolab.cs.cmu.edu/15122-f13/clac
