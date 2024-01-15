#ifndef _MALLOC_H_
# define _MALLOC_H_

#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

#define TINY_ZONE_SIZE getpagesize() * 8
#define SMALL_ZONE_SIZE getpagesize() * 32
#define MEM_METADATA_SIZE sizeof(t_mem)
#define ALLOC_METADATA_SIZE sizeof(t_alloc)
#define TINY_ALLOC_SIZE (TINY_ZONE_SIZE - MEM_METADATA_SIZE) / 128
#define SMALL_ALLOC_SIZE (SMALL_ZONE_SIZE - MEM_METADATA_SIZE) / 128
#define TINY_ALLOC_SPACE TINY_ALLOC_SIZE - ALLOC_METADATA_SIZE
#define SMALL_ALLOC_SPACE SMALL_ALLOC_SIZE - ALLOC_METADATA_SIZE

typedef struct s_mem {
    struct t_alloc *first_block;
    struct s_mem *next;
    struct s_mem *prev;
    size_t size;
    size_t block_size;
    size_t free_block;
} t_mem;

typedef struct s_alloc {
    void *ptr;
    struct t_alloc *next;
    struct t_alloc *prev;
    size_t size;
    int is_free;
} t_alloc;

void    *malloc(size_t size);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);
size_t	ft_strlen(const char *str);
void	ft_putnbr_fd(int n, int fd);
void print_allocation_strat(void);

#endif