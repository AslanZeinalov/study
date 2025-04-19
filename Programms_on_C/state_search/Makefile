CC = gcc -Wall -Wextra -Werror -std=c99

all: state_search

state_search: state_search.o
	$(CC) state_search.o -o state_search

state_search.o: state_search.c
	$(CC) -c state_search.c -o state_search.o

clean:
	rm *.o state_search

run: all
	./state_search
