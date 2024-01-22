#include "ft_malloc.h"

extern t_mem ft_data;

// static void* search_available_mem_segment(size_t size)
// {
//     t_mem *mem_ptr = &ft_data;
//     void *ptr = NULL;

//     while (mem_ptr->next != NULL)
//     {
//         if (mem_ptr->mem_size >= size && mem_ptr->free_alloc >= 1)
//         {
//             struct s_alloc *alloc_ptr = mem_ptr->first_alloc;
//             while (alloc_ptr->next != NULL)
//             {
//                 if (alloc_ptr->is_free == 1)
//                 {
//                     alloc_ptr->is_free = 0;
//                     ptr = alloc_ptr->ptr;
//                 }
//                 alloc_ptr = alloc_ptr->next;
//             }
//         }
//     }
//     while (mem_ptr->prev != NULL){
//         mem_ptr = mem_ptr->prev;
//     }
//     return (ptr);
// }

static void* create_new_mem_segment(size_t size)
{
    t_mem *mem_ptr = &ft_data;
    void *ret_ptr = NULL;
    size_t mem_size = 0;
    size_t alloc_size = 0;

    if (size <= TINY_ALLOC_SPACE) {
        mem_size = TINY_ZONE_SIZE;
        alloc_size = TINY_ALLOC_SIZE;
    }
    else if (size <= SMALL_ALLOC_SPACE) {
        mem_size = SMALL_ZONE_SIZE;
        alloc_size = SMALL_ALLOC_SIZE;
    }
    else {
        mem_size = size + MEM_METADATA_SIZE + ALLOC_METADATA_SIZE;
        alloc_size = size + ALLOC_METADATA_SIZE;
    }

    while (mem_ptr->next != NULL)
        mem_ptr = mem_ptr->next;
    mem_ptr->next = (t_mem*) mmap(NULL, mem_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem_ptr->next == MAP_FAILED)
        return (write(1, "Error: mmap failed\n", 19), NULL);
    mem_ptr->next->prev = mem_ptr;
    mem_ptr = mem_ptr->next;    
    mem_ptr->size = mem_size;
    mem_ptr->next = NULL;

    t_alloc* alloc_ptr = mem_ptr->first_alloc;
    alloc_ptr = (t_alloc*) mem_ptr + MEM_METADATA_SIZE;
    alloc_ptr->prev = NULL;
    alloc_ptr->next = NULL;
    alloc_ptr->ptr = alloc_ptr + ALLOC_METADATA_SIZE;
    alloc_ptr->is_free = true;
    alloc_ptr->size = size;

    ret_ptr = alloc_ptr->ptr;
    
    print_allocation_strat();
    write(1, "\n", 1);
    write(1, "\n", 1);
    write(1, "\n", 1);

    int i = 0;
    write(1, "alloc_size = ", 13);
    ft_putnbr_fd(alloc_size, 1);
    while (++i < 128)
    {
        write(1, "\n", 1);
        write(1, "i = ", 4);
        ft_putnbr_fd(i, 1);
        write(1, "\n", 1); 
        write(1, "alloc_ptr = ", 12);
        ft_putnbr_fd(alloc_size, 1);
        alloc_ptr->next = (t_alloc*) alloc_ptr + alloc_size;
        write(1, "\n", 1);
        write(1, "5", 1);
        alloc_ptr->next->prev = alloc_ptr;
        write(1, "1", 1);
        alloc_ptr = alloc_ptr->next;
        write(1, "2", 1);
        alloc_ptr->ptr = alloc_ptr + ALLOC_METADATA_SIZE;
        write(1, "3", 1);
        alloc_ptr->is_free = true;
        write(1, "4", 1);
    }
    while (alloc_ptr->prev != NULL){
        alloc_ptr = alloc_ptr->prev;
    }
    while (mem_ptr->prev != NULL){
        mem_ptr = mem_ptr->prev;
    }
    return (ret_ptr);
}

void *malloc(size_t size)
{
    void *ptr = NULL;

    // ptr = search_available_mem_segment(size);
    if (ptr == NULL){
        ptr = create_new_mem_segment(size);
    }
    show_alloc_mem();

    return (NULL);
}

