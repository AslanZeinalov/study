CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
TARGET = text_processor

OBJS = text_processor.o s21_string.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

s21_string.o: s21_string.c s21_string.h
	$(CC) $(CFLAGS) -c s21_string.c -o s21_string.o

text_processor.o: text_processor.c s21_string.h
	$(CC) $(CFLAGS) -c text_processor.c -o text_processor.o

clean:
	rm -f *.o $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
