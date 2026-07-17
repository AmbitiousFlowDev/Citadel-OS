#include "filesystem.h"

#include "tty.h"
#include "utils.h"

static File files[FS_MAX_FILES];

static File *filesystem_find(const char *name)
{
    for (int i = 0; i < FS_MAX_FILES; i++)
    {
        if (!files[i].used)
            continue;

        if (strcmp(files[i].name, name) == 0)
            return &files[i];
    }

    return NULL;
}

static File *filesystem_allocate(void)
{
    for (int i = 0; i < FS_MAX_FILES; i++)
    {
        if (!files[i].used)
            return &files[i];
    }

    return NULL;
}

void filesystem_init(void)
{
    memset(files, 0, sizeof(files));
}

int filesystem_exists(const char *name)
{
    return filesystem_find(name) != NULL;
}

int filesystem_create(const char *name)
{
    if (filesystem_exists(name))
        return 0;

    File *file = filesystem_allocate();

    if (file == NULL)
        return 0;

    file->used = 1;

    strcpy(file->name, name);

    file->size = 0;

    file->data[0] = '\0';

    return 1;
}

int filesystem_delete(const char *name)
{
    File *file = filesystem_find(name);

    if (file == NULL)
        return 0;

    memset(file, 0, sizeof(File));

    return 1;
}

int filesystem_write(const char *name, const char *text)
{
    File *file = filesystem_find(name);

    if (file == NULL)
        return 0;

    strncpy(file->data, text, FS_FILE_SIZE - 1);

    file->data[FS_FILE_SIZE - 1] = '\0';

    file->size = strlen(file->data);

    return 1;
}

const char *filesystem_read(const char *name)
{
    File *file = filesystem_find(name);

    if (file == NULL)
        return NULL;

    return file->data;
}

void filesystem_list(void)
{
    int empty = 1;

    for (int i = 0; i < FS_MAX_FILES; i++)
    {
        if (!files[i].used)
            continue;

        tty_write(files[i].name);
        tty_write(" (");

        char buffer[16];
        utoa((uint32_t)files[i].size, buffer);

        tty_write(buffer);
        tty_writeln(" bytes)");

        empty = 0;
    }

    if (empty)
    {
        tty_writeln("No files.");
    }
}
