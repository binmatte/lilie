#ifndef LILIE_COLIE_H
#define LILIE_COLIE_H

#include <stdio.h>
#include <stdlib.h>

#define ANSI_FG_BLACK          "\033[30m"
#define ANSI_FG_RED            "\033[31m"
#define ANSI_FG_GREEN          "\033[32m"
#define ANSI_FG_YELLOW         "\033[33m"
#define ANSI_FG_BLUE           "\033[34m"
#define ANSI_FG_MAGENTA        "\033[35m"
#define ANSI_FG_CYAN           "\033[36m"
#define ANSI_FG_WHITE          "\033[37m"

#define ANSI_BG_BLACK          "\033[40m"
#define ANSI_BG_RED            "\033[41m"
#define ANSI_BG_GREEN          "\033[42m"
#define ANSI_BG_YELLOW         "\033[43m"
#define ANSI_BG_BLUE           "\033[44m"
#define ANSI_BG_MAGENTA        "\033[45m"
#define ANSI_BG_CYAN           "\033[46m"
#define ANSI_BG_WHITE          "\033[47m"

#define ANSI_RESET             "\033[0m"
#define ANSI_BOLD              "\033[1m"
#define ANSI_DIM               "\033[2m"
#define ANSI_ITALIC            "\033[3m"
#define ANSI_UNDERLINE         "\033[4m"
#define ANSI_BLINK             "\033[5m"
#define ANSI_INVERT            "\033[7m"
#define ANSI_HIDDEN            "\033[8m"
#define ANSI_STRIKE            "\033[9m"

typedef enum {
    COLIE_BLACK,
    COLIE_RED,
    COLIE_GREEN,
    COLIE_YELLOW,
    COLIE_BLUE,
    COLIE_MAGENTA,
    COLIE_CYAN,
    COLIE_WHITE
} ColieColor;

typedef enum {
    COLIE_RESET,
    COLIE_BOLD,
    COLIE_DIM,
    COLIE_ITALIC,
    COLIE_UNDERLINE,
    COLIE_BLINK,
    COLIE_INVERT,
    COLIE_HIDDEN,
    COLIE_STRIKE,
} ColieAttr;

const char * colieFG(ColieColor color) {
    switch (color) {
        case COLIE_BLACK: return ANSI_FG_BLACK;
        case COLIE_RED: return ANSI_FG_RED;
        case COLIE_GREEN: return ANSI_FG_GREEN;
        case COLIE_YELLOW: return ANSI_FG_YELLOW;
        case COLIE_BLUE: return ANSI_FG_BLUE;
        case COLIE_MAGENTA: return ANSI_FG_MAGENTA;
        case COLIE_CYAN: return ANSI_FG_CYAN;
        case COLIE_WHITE: return ANSI_FG_WHITE;
        default: return "";
    }
}

const char * colieBG(ColieColor color) {
    switch (color) {
        case COLIE_BLACK: return ANSI_BG_BLACK;
        case COLIE_RED: return ANSI_BG_RED;
        case COLIE_GREEN: return ANSI_BG_GREEN;
        case COLIE_YELLOW: return ANSI_BG_YELLOW;
        case COLIE_BLUE: return ANSI_BG_BLUE;
        case COLIE_MAGENTA: return ANSI_BG_MAGENTA;
        case COLIE_CYAN: return ANSI_BG_CYAN;
        case COLIE_WHITE: return ANSI_BG_WHITE;
        default: return "";
    }
}

const char * colieFGExtended(unsigned char color) {
    if (color <= 255) {
        static char buffer[16];
        snprintf(buffer, sizeof(buffer), "\033[38;5;%dm", color);
        return buffer;
    }
    return "";
}

const char * colieBGExtended(unsigned char color) {
    if (color <= 255) {
        static char buffer[16];
        snprintf(buffer, sizeof(buffer), "\033[48;5;%dm", color);
        return buffer;
    }
    return "";
}

const char * colieFGRGB(unsigned char r, unsigned char g, unsigned char b) {
    static char buffer[20];
    snprintf(buffer, sizeof(buffer), "\033[38;2;%d;%d;%dm", r, g, b);
    return buffer;
}

const char * colieBGRGB(unsigned char r, unsigned char g, unsigned char b) {
    static char buffer[20];
    snprintf(buffer, sizeof(buffer), "\033[48;2;%d;%d;%dm", r, g, b);
    return buffer;
}

const char * colieAttr(ColieAttr attr) {
    switch (attr) {
        case COLIE_RESET: return ANSI_RESET;
        case COLIE_BOLD: return ANSI_BOLD;
        case COLIE_DIM: return ANSI_DIM;
        case COLIE_ITALIC: return ANSI_ITALIC;
        case COLIE_UNDERLINE: return ANSI_UNDERLINE;
        case COLIE_BLINK: return ANSI_BLINK;
        case COLIE_INVERT: return ANSI_INVERT;
        case COLIE_HIDDEN: return ANSI_HIDDEN;
        case COLIE_STRIKE: return ANSI_STRIKE;
        default: return "";
    }
}

#endif // LILIE_COLIE_H
