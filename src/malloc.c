#include "ft_malloc.h"

extern t_mem ft_data;

static void* search_available_mem_segment(size_t size)
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
    while (mem_ptr->prev != NULL){
        mem_ptr = mem_ptr->prev;
    }
    return (ptr);
}

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



    mem_ptr->ptr = mmap(NULL, TINY_ALLOC_SPACE, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);

    mem_ptr->

    // while (mem_ptr->next != NULL){
    //     mem_ptr = mem_ptr->next;
    // }
    // mem_ptr->next->ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);
    // mem_ptr->next->prev = mem_ptr;
    // mem_ptr = mem_ptr->next;
    // mem_ptr->alloc_size = size;
    // mem_ptr->free_alloc = false;

    // if (size == TINY_ZONE_SIZE) {
    //     t_alloc *alloc_ptr = mem_ptr->first_alloc;
    //     for (int i = 0; i < 128; i++) {
    //         alloc_ptr->ptr = mem_ptr->ptr + MEM_METADATA_SIZE + (i * TINY_ALLOC_SIZE);


    //         mem_ptr->first_alloc->ptr = mem_ptr->ptr + MEM_METADATA_SIZE + ALLOC_METADATA_SIZE;
    //         mem_ptr->first_alloc->is_free = true;
    //         mem_ptr->first_alloc->next = mem_ptr->first_alloc + ALLOC_METADATA_SIZE;
    //         mem_ptr->first_alloc->prev = NULL;
    //         mem_ptr->first_alloc = mem_ptr->first_alloc->next;
    //     }

    //     mem_ptr->first_alloc->ptr = mem_ptr->ptr + MEM_METADATA_SIZE + ALLOC_METADATA_SIZE;

    // }
    // else if (size == SMALL_ZONE_SIZE) {



    // }
    // else {
    //     mem_ptr->first_alloc->ptr = mem_ptr->ptr + MEM_METADATA_SIZE + ALLOC_METADATA_SIZE;
    //     mem_ptr->first_alloc->is_free = false;
    // }







    // mem_ptr->first_alloc = mem_ptr->next + MEM_METADATA_SIZE;
    // mem_ptr->first_alloc->ptr = mem_ptr->first_alloc + ALLOC_METADATA_SIZE;
    // mem_ptr->first_alloc->is_free = 0;
    // mem_ptr->first_alloc->next = NULL;
    // mem_ptr->first_alloc->prev = NULL;
    // ptr = mem_ptr->first_alloc->ptr;
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

