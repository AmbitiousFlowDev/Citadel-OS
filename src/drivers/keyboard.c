#include <keyboard.h>

#define PS2_DATA 0x60
#define PS2_STATUS 0x64

static inline uint8_t inb(uint16_t port)
{
    uint8_t value;

    __asm__ volatile(
        "inb %1, %0"
        : "=a"(value)
        : "Nd"(port));

    return value;
}

bool keyboard_available(void)
{
    return inb(PS2_STATUS) & 1;
}
