#include "ft_malloc.h"

void print_allocation_strat(void) {

    write(1, "\nTINY_ZONE_SIZE\n", 16);
    ft_putnbr_fd(TINY_ZONE_SIZE, 1);
    write(1, "\nSMALL_ZONE_SIZE\n", 17);
    ft_putnbr_fd(SMALL_ZONE_SIZE, 1);
    write(1, "\nMEM_METADATA_SIZE\n", 19);
    ft_putnbr_fd(MEM_METADATA_SIZE, 1);
    write(1, "\nALLOC_METADATA_SIZE\n", 21);
    ft_putnbr_fd(ALLOC_METADATA_SIZE, 1);
    write(1, "\nTINY_ALLOC_SIZE\n", 17);
    ft_putnbr_fd(TINY_ALLOC_SIZE, 1);
    write(1, "\nSMALL_ALLOC_SIZE\n", 18);
    ft_putnbr_fd(SMALL_ALLOC_SIZE, 1);
    write(1, "\nTINY_ALLOC_SPACE\n", 18);
    ft_putnbr_fd(TINY_ALLOC_SPACE, 1);
    write(1, "\nSMALL_ALLOC_SPACE\n", 19);
    ft_putnbr_fd(SMALL_ALLOC_SPACE, 1);
}

