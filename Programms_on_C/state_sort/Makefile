CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
TARGET = state_sort

all: $(TARGET)

$(TARGET): state_sort.o
	$(CC) $(CFLAGS) state_sort.o -o $(TARGET)

state_sort.o: state_sort.c
	$(CC) $(CFLAGS) -c state_sort.c -o state_sort.o

clean: 
	rm -f *.o $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
