CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = cipher
LOGGER_DIR = logger
OBJ_DIR = obj

SRCS = cipher.c $(LOGGER_DIR)/logger.c
OBJS = $(addprefix $(OBJ_DIR)/,$(notdir $(SRCS:.c=.o)))

all: $(TARGET)

$(TARGET): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/cipher.o: cipher.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/logger.o: $(LOGGER_DIR)/logger.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

rebuild: clean all

run:
	./$(TARGET)
