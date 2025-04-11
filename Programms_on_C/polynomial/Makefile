CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g -lm

TARGET = polynomial

all: $(TARGET)

$(TARGET): polynomial.o
	$(CC) $(CFLAGS) polynomial.o -o $(TARGET) -lm

polynomial.o: polynomial.c
	$(CC) $(CFLAGS) -c polynomial.c -o polynomial.o -lm

clean:
	rm -f *.o $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
