CC = gcc
FLAGS = -Wall -Werror -g
TARGET = bst_create_test

OBJS = bst.o bst_create_test.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJS)

bst.o: bst.c bst.h
	$(CC) $(FLAGS) -c bst.c -o bst.o

bst_create_test.o: bst_create_test.c bst.h
	$(CC) $(FLAGS) -c bst_create_test.c -o bst_create_test.o

clean: 
	rm -f *.o $(TARGET)

rebuild: clean all

run: 
	./$(TARGET)

.PHONY: all clean rebuild run
