#include "ft_malloc.h"

extern t_mem ft_data;

// static void* search_available_mem_segment(size_t size)
// {
//     t_mem *mem_ptr = &ft_data;
//     void *ptr = NULL;

//     while (mem_ptr->next != NULL)
//     {
//         if (mem_ptr->alloc_size >= size && mem_ptr->free_alloc >= 1)
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
    void *ptr = NULL;

    if (size <= TINY_ALLOC_SPACE)
        size = TINY_ZONE_SIZE;
    else if (size <= SMALL_ALLOC_SPACE)
        size = SMALL_ZONE_SIZE;
    else
        size = size + MEM_METADATA_SIZE + ALLOC_METADATA_SIZE;

    while (mem_ptr->next != NULL)
        mem_ptr = mem_ptr->next;
    mem_ptr->next = (t_mem*) mmap(NULL, TINY_ALLOC_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem_ptr->next == MAP_FAILED)
        return (write(1, "Error: mmap failed\n", 19), NULL);
    mem_ptr->next->prev = mem_ptr;
    mem_ptr = mem_ptr->next;    
    mem_ptr->alloc_size = size;
    mem_ptr->next = NULL;

    t_alloc* alloc_ptr = mem_ptr->first_alloc;
    alloc_ptr = (t_alloc*) mem_ptr + MEM_METADATA_SIZE;
    alloc_ptr->prev = NULL;
    alloc_ptr->next = NULL;
    alloc_ptr->ptr = alloc_ptr + ALLOC_METADATA_SIZE;
    alloc_ptr->is_free = true;
    
    int i = 0;
    while (++i < 128)
    {
        alloc_ptr->next = (t_alloc*) alloc_ptr + (((size - MEM_METADATA_SIZE) / 128) * i);
        alloc_ptr->next->prev = alloc_ptr;
        alloc_ptr = alloc_ptr->next;
        alloc_ptr->ptr = alloc_ptr + ALLOC_METADATA_SIZE;
        alloc_ptr->is_free = true;
    }
    while (alloc_ptr->prev != NULL){
        alloc_ptr = alloc_ptr->prev;
    }
    while (mem_ptr->prev != NULL){
        mem_ptr = mem_ptr->prev;
    }
    return (ptr);
}

void *malloc(size_t size)
{
    void *ptr = NULL;

    // ptr = search_available_mem_segment(size);
    if (ptr == NULL){
        ptr = create_new_mem_segment(size);
    }
    return (NULL);
}

