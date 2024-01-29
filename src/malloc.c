#include "ft_malloc.h"
#include <stdio.h>

extern t_mem* ft_data;

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

// static unsigned long maxStackSize(void) {

//     struct rlimit rlim;
//     // Get the current stack size limit
//     if (getrlimit(RLIMIT_STACK, &rlim) != 0)
//         return 0;
//     // return rlim.rlim_cur;

//     return rlim.rlim_max;
// }

static size_t which_mem_size(size_t size) {

    if (size <= TINY_ALLOC_SPACE)
        return TINY_ZONE_SIZE;
    if (size <= SMALL_ALLOC_SPACE)
        return SMALL_ZONE_SIZE;
    return size + MEM_METADATA_SIZE + ALLOC_METADATA_SIZE;
}

static size_t which_alloc_size(size_t size) {

    if (size <= TINY_ALLOC_SPACE)
        return TINY_ALLOC_SIZE;
    if (size <= SMALL_ALLOC_SPACE)
        return SMALL_ALLOC_SIZE;
    return size + ALLOC_METADATA_SIZE;
}

static void* create_new_mem_segment(size_t size)
{
    size_t i = 0;
    size_t mem_size = which_mem_size(size);
    size_t alloc_size = which_alloc_size(size);
    (void)alloc_size;

    ft_data = (t_mem*)mmap(NULL, mem_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    t_mem *mem_ptr = ft_data;
    if (mem_ptr->next == MAP_FAILED)
        return(write(1, "MAP_FAILED\n", 11), NULL);
    mem_ptr->prev = NULL;
    // if (mem_ptr->next == NULL) {
    // } else {
    //     while (mem_ptr->next != NULL) 
    //         mem_ptr = mem_ptr->next;
    //     mem_ptr->next = (t_mem*)mmap(NULL, mem_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    //     if (mem_ptr->next == MAP_FAILED)
    //         return(write(1, "MAP_FAILED\n", 11), NULL);
    //     mem_ptr->next->prev = mem_ptr;
    //     mem_ptr = mem_ptr->next;
    // }

    mem_ptr->size = mem_size;
    mem_ptr->next = NULL;
    i += MEM_METADATA_SIZE;

    mem_ptr->first_alloc = (t_alloc*)((char*)(mem_ptr + i));
    i += ALLOC_METADATA_SIZE;
    t_alloc* alloc_ptr = mem_ptr->first_alloc;
    alloc_ptr->prev = NULL;
    alloc_ptr->next = NULL;
    alloc_ptr->is_free = true;
    alloc_ptr->size = alloc_size;
    alloc_ptr->ptr = (void*)((char*)(mem_ptr + i));
    i += alloc_size - ALLOC_METADATA_SIZE;
    void* ret_ptr = alloc_ptr->ptr;

    while ((i + alloc_size) < mem_size) {
        alloc_ptr->next = (t_alloc*)((char*)mem_ptr + i);
        i += ALLOC_METADATA_SIZE;
        alloc_ptr->next->prev = alloc_ptr;
        alloc_ptr = alloc_ptr->next;
        alloc_ptr->is_free = true;
        alloc_ptr->ptr = ((char*)(mem_ptr + i));
        alloc_ptr->size = alloc_size;
        alloc_ptr->next = NULL;
        i += alloc_size - ALLOC_METADATA_SIZE;
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

