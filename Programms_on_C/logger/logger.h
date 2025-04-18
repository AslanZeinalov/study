#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>

typedef enum {
    DEBUG,
    INFO,
    WARNING,
    ERROR
} log_level;

int log_init(char *filename);
void log(char *message, log_level level);
void log_close();

#endif
