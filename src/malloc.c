#include "ft_malloc.h"

void *malloc(size_t size)
{
    // print_allocation_strat();

    

    write(1, "\nmalloc\n", 8);
    (void)size;
    return (NULL);
}

