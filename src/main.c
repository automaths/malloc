#include "ft_malloc.h"

t_mem* ft_data;

int main()
{
    void *ptr = malloc(50);
    if (0) {
        ptr = realloc(ptr, 20);
        free(ptr);
        char i = ft_strlen("Hello World") + 65;
        write(1, &i, 1);
        (void)ptr;
    }
    return (0);
}