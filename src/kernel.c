#include "tty.h"
#include "keyboard.h"
#include "filesystem.h"
#include "shell.h"

void kernel_main(void)
{
    tty_init();
    keyboard_init();
    filesystem_init();

    tty_writeln("======================================");
    tty_writeln("        Citadel Operating System");
    tty_writeln("======================================");
    tty_writeln("");

    shell_run();

    for (;;)
    {
        __asm__ volatile("hlt");
    }
}