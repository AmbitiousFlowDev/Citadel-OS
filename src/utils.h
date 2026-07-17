#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char *str);

int strcmp(const char *a, const char *b);

int strncmp(const char *a, const char *b, size_t n);

char *strcpy(char *dest, const char *src);

char *strncpy(char *dest, const char *src, size_t n);

char *strcat(char *dest, const char *src);

char *strchr(const char *str, int c);

void *memset(void *ptr, int value, size_t size);

void *memcpy(void *dest, const void *src, size_t size);

int memcmp(const void *a, const void *b, size_t size);

char to_upper(char c);

char to_lower(char c);

int is_alpha(char c);

int is_digit(char c);

int is_space(char c);

int atoi(const char *str);

void itoa(int value, char *buffer);

void utoa(uint32_t value, char *buffer);

void xtoa(uint32_t value, char *buffer);

void reverse(char *str);

void trim(char *str);

void* memmove(void* dest, const void* src, size_t size);

void split_first(
    const char *input,
    char *command,
    char *arguments);

#endif
