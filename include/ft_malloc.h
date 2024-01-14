#ifndef _MALLOC_H_
# define _MALLOC_H_

#include <unistd.h>

void    *malloc(size_t size);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);
size_t	ft_strlen(const char *str);

#endif