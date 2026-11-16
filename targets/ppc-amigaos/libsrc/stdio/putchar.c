#include <stdio.h>

#undef putchar

int putchar(int character)
{
    return putc(character,stdout);
}
