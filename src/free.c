#include "ft_malloc.h"
#include <string.h>
#include <errno.h>

extern t_mem* ft_data;

void free(void *ptr)
{
    t_mem *mem_ptr = ft_data;
    bool found = false;


    if (ptr == NULL)
        return;
    while (mem_ptr != NULL) {

        t_alloc *alloc_ptr = mem_ptr->first_alloc;
        while (alloc_ptr != NULL) {
            if (alloc_ptr->ptr == ptr) {
                alloc_ptr->is_free = true;
                mem_ptr->used_allocations -= 1;
                found = true;
                break;
            }
            if (alloc_ptr->next == NULL)
                break;
            alloc_ptr = alloc_ptr->next;
        }
        while (alloc_ptr->prev != NULL)
            alloc_ptr = alloc_ptr->prev;
        if (found == true || mem_ptr->next == NULL)
            break;
        mem_ptr = mem_ptr->next;
    }

    if (mem_ptr->used_allocations <= 0) {
        if (mem_ptr->prev != NULL && mem_ptr->next != NULL) {
            mem_ptr->prev->next = mem_ptr->next;
            mem_ptr->next->prev = mem_ptr->prev;
        } else if (mem_ptr->next != NULL) {
            ft_data = mem_ptr->next;
            mem_ptr->next->prev = NULL;
        } else if (mem_ptr->prev != NULL) {
            mem_ptr->prev->next = NULL;
        }
        else {
            // ft_data = NULL;
        }
        // int ret = munmap(mem_ptr, mem_ptr->size);
        if (munmap(mem_ptr, mem_ptr->size) != 0) {
            write(1, "munmap failed\n", 14);
            write(1, strerror(errno), ft_strlen(strerror(errno)));
            // strerror(errno);   
        }
        mem_ptr = ft_data;
    }
    mem_ptr = ft_data;
}
