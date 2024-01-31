#include "ft_malloc.h"

t_mem* ft_data;

int main()
{
    void* ptr = malloc(50);
    void* ptr2 = malloc(50);
    void* ptr3 = malloc(5000);
    (void)ptr2;
    (void)ptr3;
    show_alloc_mem();
    ptr = realloc(ptr, 500);
    show_alloc_mem();

    if (0) {
        ptr = realloc(ptr, 20);
        free(ptr);
        char i = ft_strlen("Hello World") + 65;
        write(1, &i, 1);
        (void)ptr;
    }
    return (0);
}