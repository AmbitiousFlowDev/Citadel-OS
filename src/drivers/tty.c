#include "tty.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static volatile uint16_t *const VGA =
    (uint16_t *)0xB8000;

static size_t cursor_x = 0;
static size_t cursor_y = 0;

static uint8_t color = 0x0F;

static inline uint16_t vga_entry(char c)
{
    return ((uint16_t)color << 8) | (uint8_t)c;
}

static inline size_t index_at(size_t x, size_t y)
{
    return y * VGA_WIDTH + x;
}

void tty_set_color(tty_color_t fg, tty_color_t bg)
{
    color = (bg << 4) | fg;
}

void tty_clear(void)
{
    for (size_t y = 0; y < VGA_HEIGHT; ++y)
    {
        for (size_t x = 0; x < VGA_WIDTH; ++x)
        {
            VGA[index_at(x, y)] = vga_entry(' ');
        }
    }

    cursor_x = 0;
    cursor_y = 0;
}

void tty_init(void)
{
    tty_set_color(TTY_COLOR_WHITE, TTY_COLOR_BLACK);
    tty_clear();
}

static void newline(void)
{
    cursor_x = 0;

    if (cursor_y < VGA_HEIGHT - 1)
        cursor_y++;
}

void tty_putchar(char c)
{
    switch (c)
    {
    case '\n':
        newline();
        return;

    case '\r':
        cursor_x = 0;
        return;

    case '\t':
        cursor_x += 4;
        return;

    default:
        break;
    }

    VGA[index_at(cursor_x, cursor_y)] = vga_entry(c);

    cursor_x++;

    if (cursor_x >= VGA_WIDTH)
        newline();
}

void tty_write(const char *str)
{
    while (*str)
        tty_putchar(*str++);
}

void tty_write_line(const char *str)
{
    tty_write(str);
    tty_putchar('\n');
}