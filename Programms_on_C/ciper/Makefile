CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = ciper

all: $(TARGET)

$(TARGET): ciper.o
	$(CC) $(CFLAGS) ciper.o -o ciper

ciper.o: ciper.c
	$(CC) $(CFLAGS) -c ciper.c -o ciper.o

clean:
	rm -f *.o $(TARGET)

rebuild: clean all

run:
	./$(TARGET)
