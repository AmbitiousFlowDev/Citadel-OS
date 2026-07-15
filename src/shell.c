#include "shell.h"

#include "tty.h"
#include "keyboard.h"
#include "filesystem.h"
#include "utils.h"

#define INPUT_SIZE 256

static char input[INPUT_SIZE];
static char command[64];
static char arguments[192];

static void shell_readline(void)
{
    int index = 0;

    while (1)
    {
        char c = keyboard_getchar();

        if (c == '\r')
            c = '\n';

        if (c == '\n')
        {
            input[index] = '\0';
            tty_putchar('\n');
            return;
        }

        if (c == '\b')
        {
            if (index > 0)
            {
                index--;
                tty_backspace();
            }

            continue;
        }

        if (index >= INPUT_SIZE - 1)
            continue;

        input[index++] = c;
        tty_putchar(c);
    }
}

static void cmd_help(void)
{
    tty_writeln("Available commands:");
    tty_writeln("");
    tty_writeln("help");
    tty_writeln("clear");
    tty_writeln("echo");
    tty_writeln("version");
    tty_writeln("about");
    tty_writeln("ls");
    tty_writeln("touch");
    tty_writeln("cat");
    tty_writeln("write");
    tty_writeln("rm");
}

static void cmd_version(void)
{
    tty_writeln("Citadel OS v0.1");
}

static void cmd_about(void)
{
    tty_writeln("Citadel OS");
    tty_writeln("Educational Operating System");
}

static void cmd_echo(void)
{
    tty_writeln(arguments);
}

static void cmd_touch(void)
{
    if (strlen(arguments) == 0)
    {
        tty_writeln("Usage: touch <name>");
        return;
    }

    if (filesystem_create(arguments))
        tty_writeln("File created.");
    else
        tty_writeln("Failed to create file.");
}

static void cmd_rm(void)
{
    if (filesystem_delete(arguments))
        tty_writeln("File deleted.");
    else
        tty_writeln("File not found.");
}

static void cmd_cat(void)
{
    const char *text = filesystem_read(arguments);

    if (text == NULL)
    {
        tty_writeln("File not found.");
        return;
    }

    tty_writeln(text);
}

static void cmd_write(void)
{
    char filename[64];
    char *text;

    split_first(arguments, filename, arguments);

    text = strchr(arguments, ' ');

    if (text)
    {
        *text = '\0';
        text++;
    }
    else
    {
        text = "";
    }

    if (!filesystem_write(filename, text))
    {
        tty_writeln("Unable to write file.");
        return;
    }

    tty_writeln("File updated.");
}

static void shell_execute(void)
{
    trim(input);

    if (strlen(input) == 0)
        return;

    split_first(input, command, arguments);

    if (strcmp(command, "help") == 0)
    {
        cmd_help();
    }
    else if (strcmp(command, "clear") == 0)
    {
        tty_clear();
    }
    else if (strcmp(command, "echo") == 0)
    {
        cmd_echo();
    }
    else if (strcmp(command, "version") == 0)
    {
        cmd_version();
    }
    else if (strcmp(command, "about") == 0)
    {
        cmd_about();
    }
    else if (strcmp(command, "ls") == 0)
    {
        filesystem_list();
    }
    else if (strcmp(command, "touch") == 0)
    {
        cmd_touch();
    }
    else if (strcmp(command, "cat") == 0)
    {
        cmd_cat();
    }
    else if (strcmp(command, "write") == 0)
    {
        cmd_write();
    }
    else if (strcmp(command, "rm") == 0)
    {
        cmd_rm();
    }
    else
    {
        tty_write("Unknown command: ");
        tty_writeln(command);
    }
}

void shell_run(void)
{
    tty_writeln("");
    tty_writeln("======================================");
    tty_writeln("        Citadel Operating System");
    tty_writeln("======================================");
    tty_writeln("Type 'help' to list commands.");
    tty_writeln("");

    while (1)
    {
        tty_write("> ");

        shell_readline();

        shell_execute();
    }
}