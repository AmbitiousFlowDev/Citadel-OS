#include "tty.h"
#include "keyboard.h"
#include "filesystem.h"
#include "shell.h"

void kernel_main(void)
{

    tty_init();

    keyboard_init();

    filesystem_init();

    tty_writeln("Booting Citadel OS...");
    tty_writeln("");

    shell_run();

    while (1)
    {
        __asm__ volatile(
            "cli\n"
            "hlt");
    }
}