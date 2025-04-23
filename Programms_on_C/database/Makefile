# Makefile

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g -Iheader_files  # -Wall включает все предупреждения, -g добавляет отладочную информацию, -Iheader_files добавляет директорию header_files в путь поиска заголовочных файлов

# Source files
SRCS = src/shared.c src/modules.c src/levels.c src/status_events.c src/modules_db.c

# Header files
HDRS = header_files/shared.h header_files/modules.h header_files/levels.h header_files/status_events.h header_files/modules_db.h

# Executable name
EXEC = modules_db

# Default target
all: $(EXEC)

# Rule to create the executable
$(EXEC): $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC)

# Clean rule
clean:
	rm -f $(EXEC)
