#pragma once

#include <stdbool.h>
#include <stdint.h>

void keyboard_init(void);

bool keyboard_available(void);

char keyboard_getchar(void);