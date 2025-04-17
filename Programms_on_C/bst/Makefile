CC = gcc
CFLAGS = -Wall -Werror -g

TARGETS = bst_create_test bst_insert_test bst_traverse_test

all: $(TARGETS)

bst_create_test: bst.o bst_create_test.o
	$(CC) $(CFLAGS) bst.o bst_create_test.o -o bst_create_test

bst_insert_test: bst.o bst_insert_test.o
	$(CC) $(CFLAGS) bst.o bst_insert_test.o -o bst_insert_test

bst_traverse_test: bst.o bst_traverse_test.o
	$(CC) $(CFLAGS) bst.o bst_traverse_test.o -o bst_traverse_test

bst.o: bst.c bst.h
	$(CC) $(CFLAGS) -c bst.c

bst_create_test.o: bst_create_test.c bst.h
	$(CC) $(CFLAGS) -c bst_create_test.c

bst_insert_test.o: bst_insert_test.c bst.h
	$(CC) $(CFLAGS) -c bst_insert_test.c

bst_traverse_test.o: bst_traverse_test.c bst.h
	$(CC) $(CFLAGS) -c bst_traverse_test.c

clean:
	rm -f *.o $(TARGETS)

rebuild: clean all

run1: 
	./bst_create_test

run2:
	./bst_insert_test

run3: 
	./bst_traverse_test

run: run1 run2 run3
