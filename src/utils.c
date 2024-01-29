#include "ft_malloc.h"
#include <stdint.h>

extern t_mem* ft_data;

void printVoidPointerAddressInHex(void *ptr, char *debug) {
    // uintptr_t address = (uintptr_t)ptr;
    // char addressString[20];
    // char *addressPtr = addressString;

    // *addressPtr++ = '0';
    // *addressPtr++ = 'x';
    // for (size_t i = 0; i < 5; ++i) {
    //     *addressPtr++ = "0123456789abcdef"[(address >> ((sizeof(uintptr_t) * 2 - 1 - i) * 4)) & 0xF];
    // }
    // *addressPtr = '\0';
    // write(1, addressString, 7);
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%p", ptr);
    write(1, debug, ft_strlen(debug));
    write(1, buffer, ft_strlen(buffer));
}

void print_allocation_strat(void) {

    write(1, "\nTINY_ZONE_SIZE\n", 16);
    ft_putnbr_fd(TINY_ZONE_SIZE, 1);
    write(1, "\nSMALL_ZONE_SIZE\n", 17);
    ft_putnbr_fd(SMALL_ZONE_SIZE, 1);
    write(1, "\nMEM_METADATA_SIZE\n", 19);
    ft_putnbr_fd(MEM_METADATA_SIZE, 1);
    write(1, "\nALLOC_METADATA_SIZE\n", 21);
    ft_putnbr_fd(ALLOC_METADATA_SIZE, 1);
    write(1, "\nTINY_ALLOC_SIZE\n", 17);
    ft_putnbr_fd(TINY_ALLOC_SIZE, 1);
    write(1, "\nSMALL_ALLOC_SIZE\n", 18);
    ft_putnbr_fd(SMALL_ALLOC_SIZE, 1);
    write(1, "\nTINY_ALLOC_SPACE\n", 18);
    ft_putnbr_fd(TINY_ALLOC_SPACE, 1);
    write(1, "\nSMALL_ALLOC_SPACE\n", 19);
    ft_putnbr_fd(SMALL_ALLOC_SPACE, 1);
}

void show_alloc_mem(void) {

    t_mem *mem_ptr = ft_data;

    while (mem_ptr != NULL)
    {
        if ((int)mem_ptr->size <= TINY_ZONE_SIZE)
            write(1, "TINY : ", 7);
        else if ((int)mem_ptr->size <= SMALL_ZONE_SIZE)
            write(1, "SMALL : ", 8);
        else
            write(1, "LARGE : ", 8);
        printVoidPointerAddressInHex((void*)mem_ptr, "");
        write(1, "\n", 1);

        t_alloc *alloc_ptr = mem_ptr->first_alloc;
        while (alloc_ptr->next != NULL)
        {
            if (alloc_ptr->is_free == false)
            {
                printVoidPointerAddressInHex((void*)alloc_ptr->ptr, "");
                write(1, " - ", 3);
                printVoidPointerAddressInHex((void*)((char*)alloc_ptr->ptr + alloc_ptr->size), "");
                write(1, " : ", 3);
                ft_putnbr_fd(alloc_ptr->size, 1);
                write(1, " bytes", 7);
                write(1, "\n", 1);
            }
            alloc_ptr = alloc_ptr->next;
        }

        while (alloc_ptr->prev != NULL)
            alloc_ptr = alloc_ptr->prev;
        if (mem_ptr->next == NULL)
            break;
        mem_ptr = mem_ptr->next;
    }
    while (mem_ptr->prev != NULL)
        mem_ptr = mem_ptr->prev;
}

