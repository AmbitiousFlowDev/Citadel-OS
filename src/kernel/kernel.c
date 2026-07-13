#include <stdint.h>

volatile uint16_t* const VGA = (uint16_t*)0xB8000;

void kernel_main(void)
{
    const char* str = "Citadel OS";

    for (int i = 0; str[i]; ++i)
        VGA[i] = 0x0F00 | str[i];

    while (1)
        __asm__ volatile ("hlt");
}