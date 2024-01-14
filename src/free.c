#include "ft_malloc.h"

void free(void *ptr)
{
    write(1, "free\n", 5);
    (void)ptr;
}
