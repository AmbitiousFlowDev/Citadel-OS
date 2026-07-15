#include "tty.h"

#include "utils.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define TAB_SIZE 4

static volatile uint16_t *const VGA =
    (volatile uint16_t *)0xB8000;

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

static void tty_scroll(void)
{
    if (cursor_y < VGA_HEIGHT)
        return;

    for (size_t y = 1; y < VGA_HEIGHT; y++)
    {
        memcpy(
            (void *)&VGA[index_at(0, y - 1)],
            (const void *)&VGA[index_at(0, y)],
            VGA_WIDTH * sizeof(uint16_t));
    }

    for (size_t x = 0; x < VGA_WIDTH; x++)
    {
        VGA[index_at(x, VGA_HEIGHT - 1)] = vga_entry(' ');
    }

    cursor_y = VGA_HEIGHT - 1;
}

static void tty_newline(void)
{
    cursor_x = 0;
    cursor_y++;

    tty_scroll();
}

void tty_init(void)
{
    tty_set_color(TTY_WHITE, TTY_BLACK);
    tty_clear();
}

void tty_clear(void)
{
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            VGA[index_at(x, y)] = vga_entry(' ');
        }
    }

    cursor_x = 0;
    cursor_y = 0;
}

void tty_set_color(tty_color_t fg, tty_color_t bg)
{
    color = (bg << 4) | fg;
}

void tty_putchar(char c)
{
    switch (c)
    {
    case '\n':
        tty_newline();
        return;

    case '\r':
        cursor_x = 0;
        return;

    case '\t':
    {
        int spaces = TAB_SIZE - (cursor_x % TAB_SIZE);

        while (spaces--)
            tty_putchar(' ');

        return;
    }

    case '\b':
        tty_backspace();
        return;
    }

    VGA[index_at(cursor_x, cursor_y)] = vga_entry(c);

    cursor_x++;

    if (cursor_x >= VGA_WIDTH)
        tty_newline();
}

void tty_write(const char *str)
{
    while (*str)
    {
        tty_putchar(*str++);
    }
}

void tty_writeln(const char *str)
{
    tty_write(str);
    tty_putchar('\n');
}

void tty_backspace(void)
{
    if (cursor_x == 0)
    {
        if (cursor_y == 0)
            return;

        cursor_y--;
        cursor_x = VGA_WIDTH - 1;
    }
    else
    {
        cursor_x--;
    }

    VGA[index_at(cursor_x, cursor_y)] = vga_entry(' ');
}

void tty_set_cursor(size_t x, size_t y)
{
    if (x >= VGA_WIDTH)
        x = VGA_WIDTH - 1;

    if (y >= VGA_HEIGHT)
        y = VGA_HEIGHT - 1;

    cursor_x = x;
    cursor_y = y;
}

size_t tty_get_cursor_x(void)
{
    return cursor_x;
}

size_t tty_get_cursor_y(void)
{
    return cursor_y;
}