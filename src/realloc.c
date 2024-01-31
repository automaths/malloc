#include "ft_malloc.h"

extern t_mem* ft_data;

void *realloc(void *ptr, size_t size)
{
    void *ret_ptr = malloc(size);
    t_alloc* ptr_metadata = find_ptr_meta(ptr);
    size_t cp_size = ptr_metadata->size < size ? ptr_metadata->size : size;

    if (ptr_metadata == NULL)
        return (NULL);
    ft_memcpy(ret_ptr, ptr, cp_size);
    write(1, "memcpy\n", 7);
    free(ptr);
    write(1, "free\n", 5);

    return (ret_ptr);
}
