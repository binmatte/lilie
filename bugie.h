#ifndef LILIE_BUGIE_H
#define LILIE_BUGIE_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdarg.h>
#include "colie.h"

#define BUGIE_LOG_BUFFER_SIZE 4096

typedef enum BugieLogLevel {
    BUGIE_LOG_LEVEL_TRACE,
    BUGIE_LOG_LEVEL_DEBUG,
    BUGIE_LOG_LEVEL_INFO,
    BUGIE_LOG_LEVEL_WARN,
    BUGIE_LOG_LEVEL_ERROR,
    BUGIE_LOG_LEVEL_FATAL
} BugieLogLevel;

typedef enum BugieTimeFormat {
    BUGIE_TIME_FORMAT_HHMMSS,
    BUGIE_TIME_FORMAT_YYYYMMDDHHMMSS,
    BUGIE_TIME_FORMAT_DDMMYYYYHHMMSS,
    BUGIE_TIME_FORMAT_CUSTOM,
} BugieTimeFormat;

static BugieTimeFormat bugie_time_format = BUGIE_TIME_FORMAT_HHMMSS;
static const char * bugie_time_format_string = NULL;
static bool bugie_use_color = true;
static FILE * bugie_stream = NULL;

void bugieInit(void) {
    bugie_stream = stdout;
}

void bugieSetTimeFormat(BugieTimeFormat time_format, const char * time_format_string) {
    if (time_format == BUGIE_TIME_FORMAT_CUSTOM) {
        bugie_time_format_string = time_format_string;
    }
    bugie_time_format = time_format;
}

void bugieSetStream(FILE * stream) {
    bugie_stream = stream;
}

void bugieEnableColor(bool state) {
    bugie_use_color = state;
}

static void bugiePrintTime(void) {
    time_t now = time(NULL);
    struct tm * timeinfo = localtime(&now);

    char time_buffer[50];

    switch (bugie_time_format) {
        case BUGIE_TIME_FORMAT_HHMMSS:
            strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", timeinfo);
            break;
        case BUGIE_TIME_FORMAT_YYYYMMDDHHMMSS:
            strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
            break;
        case BUGIE_TIME_FORMAT_DDMMYYYYHHMMSS:
            strftime(time_buffer, sizeof(time_buffer), "%d/%m/%Y %H:%M:%S", timeinfo);
            break;
        case BUGIE_TIME_FORMAT_CUSTOM:
            strftime(time_buffer, sizeof(time_buffer), bugie_time_format_string, timeinfo);
            break;
        default:
            strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", timeinfo);
            break;
    }

    if (bugie_use_color) {
        fprintf(bugie_stream, "[%s%s%s]", colieFGExtended(242), time_buffer, ANSI_RESET);
    } else {
        fprintf(bugie_stream, "[%s]", time_buffer);
    }
}

static const char * logLevelToString(BugieLogLevel level) {
    switch (level) {
        case BUGIE_LOG_LEVEL_TRACE: return "TRACE";
        case BUGIE_LOG_LEVEL_DEBUG: return "DEBUG";
        case BUGIE_LOG_LEVEL_INFO: return "INFO";
        case BUGIE_LOG_LEVEL_WARN: return "WARN";
        case BUGIE_LOG_LEVEL_ERROR: return "ERROR";
        case BUGIE_LOG_LEVEL_FATAL: return "FATAL";
        default: return "UNKNOWN";
    }
}

void bugieLog(BugieLogLevel level, const char * context, const char * message) {
    const char * level_color = "";

    switch (level) {
        case BUGIE_LOG_LEVEL_TRACE: break;
        case BUGIE_LOG_LEVEL_DEBUG: level_color = colieFGExtended(7); break;
        case BUGIE_LOG_LEVEL_INFO: level_color = ANSI_FG_BLUE; break;
        case BUGIE_LOG_LEVEL_WARN: level_color = ANSI_FG_YELLOW; break;
        case BUGIE_LOG_LEVEL_ERROR: level_color = ANSI_FG_RED; break;
        case BUGIE_LOG_LEVEL_FATAL: level_color = ANSI_BOLD ANSI_FG_RED; break;
        default: break;
    }

    bugiePrintTime();

    if (bugie_use_color) {
        fprintf(bugie_stream, "[%s%s%s] %s: %s\n",
                level_color, logLevelToString(level), ANSI_RESET, context, message);
    } else {
        fprintf(bugie_stream, "[%s] %s: %s\n", logLevelToString(level), context, message);
    }
}

void bugieLogF(BugieLogLevel level, const char * context, const char * format, ...) {
    const char * level_color = "";

    switch (level) {
        case BUGIE_LOG_LEVEL_TRACE: break;
        case BUGIE_LOG_LEVEL_DEBUG: level_color = colieFGExtended(7); break;
        case BUGIE_LOG_LEVEL_INFO: level_color = ANSI_FG_BLUE; break;
        case BUGIE_LOG_LEVEL_WARN: level_color = ANSI_FG_YELLOW; break;
        case BUGIE_LOG_LEVEL_ERROR: level_color = ANSI_FG_RED; break;
        case BUGIE_LOG_LEVEL_FATAL: level_color = ANSI_BOLD ANSI_FG_RED; break;
        default: break;
    }

    bugiePrintTime();

    char buffer[BUGIE_LOG_BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (bugie_use_color) {
        fprintf(bugie_stream, "[%s%s%s] %s: %s\n",
                level_color, logLevelToString(level), ANSI_RESET, context, buffer);
    } else {
        fprintf(bugie_stream, "[%s] %s: %s\n", logLevelToString(level), context, buffer);
    }
}

#endif // LILIE_BUGIE_H
