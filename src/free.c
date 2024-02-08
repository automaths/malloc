#include "ft_malloc.h"

extern t_mem* ft_data;

void free(void *ptr)
{
    t_mem *mem_ptr = ft_data;
    bool found = false;

    write(1, "the pointer given is: ", 23);
    printVoidPointerAddressInHex(ptr, "");
    write(1, "\n", 1);

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
        write(1, "the pointer before reorga is ", 29);
        printVoidPointerAddressInHex((void*)mem_ptr, "");
        write(1, "\n", 1);
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
            write(1, "freeing the last pointer\n", 25);
            ft_data = NULL;
        }
        write(1, "the pointer that is free is", 27);
        printVoidPointerAddressInHex((void*)mem_ptr, "");
        write(1, "\n", 1);
        ft_putnbr_fd(mem_ptr->size, 1);
        write(1, "\n", 1);
        write(1, "the pointer after REORGA IS\n", 28);
        int test = mem_ptr->size % getpagesize();
        if (test != 0) {
            write(1, "the size is not a multiple of pagesize\n", 40);
            mem_ptr->size = mem_ptr->size - test;
        }
        write(1, "munmap\n", 7);
        // int ret = munmap(mem_ptr, mem_ptr->size);
        if (munmap(mem_ptr, mem_ptr->size) != 0)
            write(1, "munmap failed\n", 14);
        mem_ptr = ft_data;
    }
    mem_ptr = ft_data;
}
