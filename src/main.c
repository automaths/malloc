#include "ft_malloc.h"

void *malloc(size_t size)
{
    write(1, "malloc\n", 7);
    (void)size;
    return (NULL);
}

void free(void *ptr)
{
    write(1, "free\n", 5);
    (void)ptr;
}

void *realloc(void *ptr, size_t size)
{
    write(1, "realloc\n", 8);
    (void)ptr;
    (void)size;
    return (NULL);
}

int main()
{
    void *ptr = malloc(10);
    ptr = realloc(ptr, 20);
    free(ptr);
    char i = ft_strlen("Hello World") + 65;
    write(1, &i, 1);
    (void)ptr;
    return (0);
}