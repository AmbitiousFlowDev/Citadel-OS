#include "keyboard.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

static inline uint8_t inb(uint16_t port)
{
    uint8_t value;

    __asm__ volatile(
        "inb %1, %0"
        : "=a"(value)
        : "Nd"(port));

    return value;
}

static const char keymap[128] =
    {
        0,
        27, /* ESC */

        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
        '-', '=',
        '\b',
        '\t',

        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
        '[', ']',
        '\n',

        0,

        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
        ';', '\'', '`',

        0,

        '\\',

        'z', 'x', 'c', 'v', 'b', 'n', 'm',
        ',', '.', '/',

        0,
        '*',

        0,

        ' ',

        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,

        0, 0, 0, 0, 0, 0, 0, 0,

        0, 0, 0,

        '7', '8', '9',
        '-',

        '4', '5', '6',
        '+',

        '1', '2', '3',

        '0',
        '.',

        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0};

void keyboard_init(void)
{
}

int keyboard_available(void)
{
    return (inb(KEYBOARD_STATUS_PORT) & 1);
}

char keyboard_getchar(void)
{
    while (1)
    {
        if (!keyboard_available())
            continue;

        uint8_t scancode = inb(KEYBOARD_DATA_PORT);

        if (scancode & 0x80)
            continue;

        if (scancode >= 128)
            continue;

        char c = keymap[scancode];

        if (c == 0)
            continue;

        return c;
    }
}