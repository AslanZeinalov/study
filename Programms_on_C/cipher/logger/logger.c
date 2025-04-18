#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

FILE *log_file;

int log_init(char *filename) {
    log_file = fopen(filename, "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        return -1;
    }
    return 0;
}

void log(char *message, log_level level) {
    if (log_file == NULL) {
        fprintf(stderr, "Log file not initialized.\n");
        return;
    }

    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    const char *level_str;
    switch (level) {
        case DEBUG:   level_str = "DEBUG";   break;
        case INFO:    level_str = "INFO";    break;
        case WARNING: level_str = "WARNING"; break;
        case ERROR:   level_str = "ERROR";   break;
        default:      level_str = "UNKNOWN"; break;
    }

    fprintf(log_file, "[%s] [%s] %s\n", timestamp, level_str, message);
    fflush(log_file);
}

void log_close() {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}
