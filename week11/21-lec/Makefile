CFLAGS = -g -DDEBUG -Wall -Wextra -Werror -std=c99 -pedantic

tst-test: ./lib/xalloc.c tst.c tst-test.c
	gcc -o tst-test ./lib/xalloc.c tst.c tst-test.c -lm $(CFLAGS)

Boggle: ./lib/xalloc.c trie.c ex1.c
	gcc -o Boggle ./lib/xalloc.c trie.c ex1.c $(CFLAGS)

trie-test: ./lib/xalloc.c trie.c trie-test.c
	gcc -o trie-test ./lib/xalloc.c trie.c trie-test.c $(CFLAGS)

clean:
	rm Boggle trie-test
