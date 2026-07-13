#pragma once

#include <stddef.h>
#include <stdint.h>

typedef enum
{
    TTY_COLOR_BLACK = 0,
    TTY_COLOR_BLUE,
    TTY_COLOR_GREEN,
    TTY_COLOR_CYAN,
    TTY_COLOR_RED,
    TTY_COLOR_MAGENTA,
    TTY_COLOR_BROWN,
    TTY_COLOR_LIGHT_GREY,
    TTY_COLOR_DARK_GREY,
    TTY_COLOR_LIGHT_BLUE,
    TTY_COLOR_LIGHT_GREEN,
    TTY_COLOR_LIGHT_CYAN,
    TTY_COLOR_LIGHT_RED,
    TTY_COLOR_PINK,
    TTY_COLOR_YELLOW,
    TTY_COLOR_WHITE
} tty_color_t;

void tty_init(void);

void tty_clear(void);

void tty_set_color(tty_color_t fg, tty_color_t bg);

void tty_putchar(char c);

void tty_write(const char* str);

void tty_write_line(const char* str);