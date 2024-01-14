#include "ft_malloc.h"

void *malloc(size_t size)
{
    // t_heap *heap;

    write(1, "\nin tiny zone\n", 14);
    ft_putnbr_fd(getpagesize() * 8, 1);
    write(1, "\none block is \n", 14);
    ft_putnbr_fd((getpagesize() * 8) / 256, 1);

    write(1, "\nin small zone\n", 15);
    ft_putnbr_fd(getpagesize() * 32, 1);
    write(1, "\none block is \n", 14);
    ft_putnbr_fd((getpagesize() * 32) / 256, 1);

    write(1, "\nin size of heap\n", 17);
    ft_putnbr_fd(sizeof(t_heap), 1);
    write(1, "\nin size of block\n", 18);
    ft_putnbr_fd(sizeof(t_block), 1);


    write(1, "\nmalloc\n", 8);
    (void)size;
    return (NULL);
}

