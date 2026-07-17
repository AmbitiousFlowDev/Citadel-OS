#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stddef.h>

#define FS_MAX_FILES 64
#define FS_FILENAME_SIZE 32
#define FS_FILE_SIZE 1024

typedef struct
{
    int used;

    char name[FS_FILENAME_SIZE];

    char data[FS_FILE_SIZE];

    size_t size;

} File;

void filesystem_init(void);

int filesystem_create(const char *name);

int filesystem_delete(const char *name);

int filesystem_exists(const char *name);

int filesystem_write(const char *name, const char *text);

const char *filesystem_read(const char *name);

void filesystem_list(void);

#endif
