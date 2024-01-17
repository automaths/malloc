#ifndef _MALLOC_H_
# define _MALLOC_H_

#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdbool.h>

#define TINY_ZONE_SIZE getpagesize() * 8
#define SMALL_ZONE_SIZE getpagesize() * 32
#define MEM_METADATA_SIZE sizeof(t_mem)
#define ALLOC_METADATA_SIZE sizeof(t_alloc)
#define TINY_ALLOC_SIZE (TINY_ZONE_SIZE - MEM_METADATA_SIZE) / 128
#define SMALL_ALLOC_SIZE (SMALL_ZONE_SIZE - MEM_METADATA_SIZE) / 128
#define TINY_ALLOC_SPACE TINY_ALLOC_SIZE - ALLOC_METADATA_SIZE
#define SMALL_ALLOC_SPACE SMALL_ALLOC_SIZE - ALLOC_METADATA_SIZE

typedef struct s_alloc {
    void *ptr;
    struct s_alloc *next;
    struct s_alloc *prev;
    int is_free;
} t_alloc;

typedef struct s_mem {
    void *ptr;
    struct s_alloc *first_alloc;
    struct s_mem *next;
    struct s_mem *prev;
    size_t alloc_size;
    bool free_alloc;
} t_mem;

void    *malloc(size_t size);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);
size_t	ft_strlen(const char *str);
void	ft_putnbr_fd(int n, int fd);
void print_allocation_strat(void);

#endif