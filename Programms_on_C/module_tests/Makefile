CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
TARGET = strlen_tests

OBJS = s21_string.o s21_string_test.o

all: strlen_tests

strlen_tests: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

s21_string.o: s21_string.c s21_string.h
	$(CC) $(CFLAGS) -c s21_string.c -o s21_string.o

s21_string_test.o: s21_string_test.c s21_string.h
	$(CC) $(CFLAGS) -c s21_string_test.c -o s21_string_test.o

clean:
	rm -f *.o $(TARGET) 
	
rebuild: clean all

.PHONY: all strlen_tests clean rebuild
