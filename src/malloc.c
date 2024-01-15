#include "ft_malloc.h"

extern t_mem ft_data;

void *malloc(size_t size)
{
    t_mem *mem_ptr = &ft_data;
    void *ptr = NULL;

    while (mem_ptr->next != NULL)
    {
        if (mem_ptr->alloc_size >= size && mem_ptr->free_alloc >= 1)
        {
            struct s_alloc *alloc_ptr = mem_ptr->first_alloc;
            while (alloc_ptr->next != NULL)
            {
                if (alloc_ptr->is_free == 1)
                {
                    alloc_ptr->is_free = 0;
                    ptr = alloc_ptr->ptr;
                }
                alloc_ptr = alloc_ptr->next;
            }
        }
    }
    if (ptr == NULL) {
        // allocate proper memory segment
    }
    while (mem_ptr->prev != NULL)
    {
        mem_ptr = mem_ptr->prev;
    }
    return (NULL);
}

