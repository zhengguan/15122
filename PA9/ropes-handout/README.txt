15-122 Principles of Imperative Computation
Ropes

==========================================================

Files you won't modify:
   rope-interface.c0 - Interface of ropes (you may optionally add new functions)
   hset.c0           - Implementation of hash sets

Files you will modify:
   hset-client.c0    - Client interface of hash sets

Files that don't exist yet:
   rope.c0           - Implementation of ropes
   rope-test.c0      - Test file with a main() function (optional)
   
==========================================================

Compiling and running your code:
   % cc0 -d -w -o rope-test rope-interface.c0 hset-client.c0 hset.c0 rope.c0 rope-test.c0
   % ./rope-test

==========================================================

If you modify rope-interface.c0 to add new functions, you'll need to
hand it in along with hset-client.c0 and rope.c0.

Submitting with Andrew handin script:
   % handin ropes hset-client.c0 rope.c0 

Creating a tarball to submit with Autolab web interface:
   % tar -czvf ropehandin.tgz hset-client.c0 rope.c0 

On autolab: https://autolab.cs.cmu.edu/15122-f14/ropes
