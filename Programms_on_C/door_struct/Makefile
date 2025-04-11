CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
TARGET = door_struct

OBJS = dmanager_module.o 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

dmanager_module.o: dmanager_module.c door_struct.h
	$(CC) $(CFLAGS) -c dmanager_module.c -o dmanager_module.o

clean:
	rm -f *.o $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild

