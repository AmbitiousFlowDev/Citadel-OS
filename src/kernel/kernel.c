#include "../drivers/tty.h"

void kernel_main(void)
{
    tty_init();

    tty_write_line("========================================");
    tty_write_line("         Citadel Operating System");
    tty_write_line("========================================");
    tty_write_line("");
    tty_write_line("Kernel initialized successfully.");
    tty_write_line("");

    while (1)
    {
        __asm__ volatile("hlt");
    }
}