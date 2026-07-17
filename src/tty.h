#ifndef TTY_H
#define TTY_H

#include <stddef.h>
#include <stdint.h>

typedef enum
{
    TTY_BLACK = 0,
    TTY_BLUE,
    TTY_GREEN,
    TTY_CYAN,
    TTY_RED,
    TTY_MAGENTA,
    TTY_BROWN,
    TTY_LIGHT_GREY,
    TTY_DARK_GREY,
    TTY_LIGHT_BLUE,
    TTY_LIGHT_GREEN,
    TTY_LIGHT_CYAN,
    TTY_LIGHT_RED,
    TTY_LIGHT_MAGENTA,
    TTY_YELLOW,
    TTY_WHITE
} tty_color_t;

void tty_init(void);

void tty_clear(void);

void tty_set_color(tty_color_t fg, tty_color_t bg);

void tty_putchar(char c);

void tty_write(const char *str);

void tty_writeln(const char *str);

void tty_backspace(void);

void tty_set_cursor(size_t x, size_t y);

size_t tty_get_cursor_x(void);

size_t tty_get_cursor_y(void);

#endif
