#ifndef _MALLOC_H_
# define _MALLOC_H_

#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

typedef struct s_heap {
    struct s_block *first_block;
    struct s_heap *next;
    struct s_heap *prev;
    size_t size;
    int is_free;
} t_heap;

typedef struct s_block {
    void *ptr;
    struct t_block *next;
    struct t_block *prev;
    size_t size;
    int is_free;
} t_block;

void    *malloc(size_t size);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);
size_t	ft_strlen(const char *str);
void	ft_putnbr_fd(int n, int fd);

#endif