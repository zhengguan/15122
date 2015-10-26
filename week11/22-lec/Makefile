CFLAGS += -DDEBUG

bst_test: bst_test.o bst.o xalloc.o
	gcc -o bst_test xalloc.o bst.o bst_test.o -lm

bst.o: bst.c
	gcc $(CFLAGS) -c bst.c -lm

bst_test.o: bst_test.c
	gcc $(CFLAGS) -c bst_test.c

xalloc.o: ../21-code/lib/xalloc.c
	gcc $(CFLAGS) -c ../21-code/lib/xalloc.c


clean:
	rm *.o
