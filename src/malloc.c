#include "ft_malloc.h"

void *malloc(size_t size)
{



    


    ft_putnbr_fd(getpagesize(), 1);


    write(1, "malloc\n", 7);
    (void)size;
    return (NULL);
}

