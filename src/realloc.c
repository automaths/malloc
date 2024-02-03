#include "ft_malloc.h"

extern t_mem* ft_data;

void *realloc(void *ptr, size_t size)
{
    void *ret_ptr = malloc(size);

    size_t max_stack_size = maxStackSize();
    if (size > max_stack_size)
        size = max_stack_size;
    if (ptr != NULL) {
        t_alloc* ptr_metadata = find_ptr_meta(ptr);
        size_t cp_size = ptr_metadata->size < size ? ptr_metadata->size : size;
        if (ptr_metadata != NULL) {
            ft_memcpy(ret_ptr, ptr, cp_size);
            free(ptr);
        }
    }

    return (ret_ptr);
}
