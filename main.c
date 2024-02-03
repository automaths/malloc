#include "ft_malloc.h"

t_mem* ft_data;

int main()
{
    // void* ptr = malloc(0);
    // void* ptr2 = malloc(50);
    // ft_putnbr_fd(maxStackSize(), 1);    
    // write(1, "coucou\n", 7);
    void* ptr3 = malloc(5000000000000000000);
    if (ptr3 == NULL)
        write(1, "NULL\n", 5);
    // write(1, "coucou\n", 7);
    // (void)ptr2;
    // (void)ptr3;
    show_alloc_mem();
    // free(ptr);
    // ptr = realloc(ptr, 500);
    // show_alloc_mem();
    // printAllocationStrat();

    return (0);
}