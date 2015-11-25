CFLAGS = -g -DDEBUG -Wall -Wextra -Werror -std=c99 -pedantic

################################################################################

#tst-test: ./lib/xalloc.c tst.c tst-test.c strbuf.c
#	gcc -o tst-test ./lib/xalloc.c strbuf.c tst.c tst-test.c -lm $(CFLAGS)

tst-test: xalloc.o strbuf.o tst.o tst-test.o queue.o
	gcc -o tst-test xalloc.o strbuf.o tst.o queue.o tst-test.o -lm $(CFLAGS)

strbuf.o: strbuf.c
	gcc -c -o strbuf.o  strbuf.c $(CFLAGS)

xalloc.o: ./lib/xalloc.c
	gcc -c -o xalloc.o ./lib/xalloc.c $(CFLAGS)

tst.o: tst.c
	gcc -c -o tst.o tst.c $(CFLAGS)

tst-test.o: tst-test.c
	gcc -c -o tst-test.o tst-test.c $(CFLAGS)

queue.o: queue.c
	gcc -c -o queue.o queue.c $(CFLAGS)
################################################################################

Boggle: ./lib/xalloc.c trie.c ex1.c
	gcc -o Boggle ./lib/xalloc.c trie.c ex1.c $(CFLAGS)

trie-test: ./lib/xalloc.c trie.c trie-test.c
	gcc -o trie-test ./lib/xalloc.c trie.c trie-test.c $(CFLAGS)

queue-test: ./lib/xalloc.c queue.c queue-test.c
	gcc -o queue-test ./lib/xalloc.c queue.c queue-test.c $(CFLAGS)

strbuf-test: ./lib/xalloc.c strbuf.c strbuf-test.c
	gcc -o strbuf-test ./lib/xalloc.c strbuf.c strbuf-test.c $(CFLAGS)

clean:
	rm Boggle trie-test
