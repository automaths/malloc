#include "ft_malloc.h"

void *realloc(void *ptr, size_t size)
{
    write(1, "realloc\n", 8);
    (void)ptr;
    (void)size;
    return (NULL);
}