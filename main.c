#include "ft_malloc.h"

t_mem* ft_data;

int main()
{
    void* ptr = malloc(0);
    void* ptr2 = malloc(50);
    void* ptr3 = malloc(5000000000000000000);
    if (ptr3 == NULL)
        write(1, "NULL\n", 5);
    void* ptr4 = malloc(500);
    void* ptr5 = malloc(5000);
    (void)ptr2;
    // (void)ptr3;
    write(1, "----------------\n", 17);
    show_alloc_mem();
    free(ptr);
    void* ptr6 = realloc(NULL, 500);
    free(ptr3);
    write(1, "----------------\n", 17);
    show_alloc_mem();
    // printAllocationStrat();

    return (0);
}