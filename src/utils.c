#include "utils.h"

size_t strlen(const char* str)
{
    size_t len = 0;

    while (str[len] != '\0')
        len++;

    return len;
}

int strcmp(const char* a, const char* b)
{
    while (*a && (*a == *b))
    {
        a++;
        b++;
    }

    return (unsigned char)*a - (unsigned char)*b;
}

int strncmp(const char* a, const char* b, size_t n)
{
    while (n && *a && (*a == *b))
    {
        a++;
        b++;
        n--;
    }

    if (n == 0)
        return 0;

    return (unsigned char)*a - (unsigned char)*b;
}

char* strcpy(char* dest, const char* src)
{
    char* start = dest;

    while ((*dest++ = *src++));

    return start;
}

char* strncpy(char* dest, const char* src, size_t n)
{
    size_t i;

    for (i = 0; i < n && src[i]; i++)
        dest[i] = src[i];

    while (i < n)
        dest[i++] = '\0';

    return dest;
}

char* strcat(char* dest, const char* src)
{
    char* ptr = dest;

    while (*ptr)
        ptr++;

    while ((*ptr++ = *src++));

    return dest;
}

char* strchr(const char* str, int c)
{
    while (*str)
    {
        if (*str == (char)c)
            return (char*)str;

        str++;
    }

    return NULL;
}

void* memset(void* ptr, int value, size_t size)
{
    uint8_t* p = (uint8_t*)ptr;

    while (size--)
        *p++ = (uint8_t)value;

    return ptr;
}

void* memcpy(void* dest, const void* src, size_t size)
{
    uint8_t* d = (uint8_t*)dest;
    const uint8_t* s = (const uint8_t*)src;

    while (size--)
        *d++ = *s++;

    return dest;
}

int memcmp(const void* a, const void* b, size_t size)
{
    const uint8_t* p1 = (const uint8_t*)a;
    const uint8_t* p2 = (const uint8_t*)b;

    while (size--)
    {
        if (*p1 != *p2)
            return *p1 - *p2;

        p1++;
        p2++;
    }

    return 0;
}

char to_upper(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 32;

    return c;
}

char to_lower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 32;

    return c;
}

int is_alpha(char c)
{
    return ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z'));
}

int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int is_space(char c)
{
    return (c == ' '  ||
            c == '\t' ||
            c == '\n' ||
            c == '\r');
}


int atoi(const char* str)
{
    int sign = 1;
    int value = 0;

    if (*str == '-')
    {
        sign = -1;
        str++;
    }

    while (is_digit(*str))
    {
        value *= 10;
        value += *str - '0';
        str++;
    }

    return value * sign;
}

void reverse(char* str)
{
    size_t len = strlen(str);

    if (len == 0)
        return;

    size_t i = 0;
    size_t j = len - 1;

    while (i < j)
    {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;

        i++;
        j--;
    }
}

void itoa(int value, char* buffer)
{
    int sign = value;
    int i = 0;

    if (value == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    if (value < 0)
        value = -value;

    while (value)
    {
        buffer[i++] = (value % 10) + '0';
        value /= 10;
    }

    if (sign < 0)
        buffer[i++] = '-';

    buffer[i] = '\0';

    reverse(buffer);
}

void utoa(uint32_t value, char* buffer)
{
    int i = 0;

    if (value == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    while (value)
    {
        buffer[i++] = (value % 10) + '0';
        value /= 10;
    }

    buffer[i] = '\0';

    reverse(buffer);
}

void xtoa(uint32_t value, char* buffer)
{
    static const char hex[] = "0123456789ABCDEF";

    int i = 0;

    if (value == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    while (value)
    {
        buffer[i++] = hex[value & 0xF];
        value >>= 4;
    }

    buffer[i] = '\0';

    reverse(buffer);
}

void trim(char* str)
{
    char* start = str;

    while (is_space(*start))
        start++;

    if (start != str)
        memmove(str, start, strlen(start) + 1);

    size_t len = strlen(str);

    while (len > 0 && is_space(str[len - 1]))
    {
        str[len - 1] = '\0';
        len--;
    }
}

void split_first(
    const char* input,
    char* command,
    char* arguments)
{
    while (*input == ' ')
        input++;

    while (*input && *input != ' ')
    {
        *command++ = *input++;
    }

    *command = '\0';

    while (*input == ' ')
        input++;

    while (*input)
    {
        *arguments++ = *input++;
    }

    *arguments = '\0';
}

void* memmove(void* dest, const void* src, size_t size)
{
    uint8_t* d = (uint8_t*)dest;
    const uint8_t* s = (const uint8_t*)src;

    if (d == s)
        return dest;

    if (d < s)
    {
        while (size--)
            *d++ = *s++;
    }
    else
    {
        d += size;
        s += size;

        while (size--)
            *--d = *--s;
    }

    return dest;
}