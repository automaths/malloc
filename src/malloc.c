#include "ft_malloc.h"
#include <stdio.h>
#include <stdint.h>

t_mem* ft_data;

void	ft_bzero(void *s, size_t n)
{
	char *str;

	str = (char *)s;
	while (n--)
		str[n] = 0;
} 

static void* search_available_mem_segment(size_t size)
{
    t_mem *mem_ptr = ft_data;
    void *ptr = NULL;

    if (mem_ptr == NULL)
        return (NULL);
    while (mem_ptr != NULL && ptr == NULL)
    {
        if (mem_ptr->first_alloc->size >= size)
        {
            struct s_alloc *alloc_ptr = mem_ptr->first_alloc;
            while (alloc_ptr->next != NULL)
            {
                if (ptr == NULL && alloc_ptr->is_free == true)
                {
                    alloc_ptr->is_free = false;
                    alloc_ptr->allocated_size = size;
                    ptr = alloc_ptr->ptr;
                    mem_ptr->used_allocations++;
                }
                alloc_ptr = alloc_ptr->next;
            }
            while (alloc_ptr->prev != NULL)
                alloc_ptr = alloc_ptr->prev;
        }
        if (mem_ptr->next == NULL)
            break;
        mem_ptr = mem_ptr->next;
    }
    while (mem_ptr->prev != NULL){
        mem_ptr = mem_ptr->prev;
    }
    return (ptr);
}

static size_t which_mem_size(size_t size) {

    size_t max_stack_size = maxStackSize();
    if ((max_stack_size < (MEM_METADATA_SIZE + ALLOC_METADATA_SIZE + 15)) || (size == 0))
        return 0;
    if ((max_stack_size < (TINY_ZONE_SIZE + MEM_METADATA_SIZE + ALLOC_METADATA_SIZE + 15)))
        return 1;
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
    size_t alloc_size;
    if (mem_size == 0)
        return NULL;
    else if (mem_size == 1) {
        mem_size = size;    
        alloc_size = maxStackSize() - MEM_METADATA_SIZE - ALLOC_METADATA_SIZE;
    }
    else
        alloc_size = which_alloc_size(size);
 
    if (ft_data == NULL) {
        ft_data = (t_mem*)mmap(NULL, mem_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        ft_bzero(ft_data, MEM_METADATA_SIZE);
        if (ft_data->next == MAP_FAILED)
            return(NULL);
        ft_data->prev = NULL;
        ft_data->size = mem_size;
        ft_data->next = NULL;
    } else {
        while (ft_data->next != NULL) {
            ft_data = ft_data->next;
        }
        ft_data->next = (t_mem*)mmap(NULL, mem_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (ft_data->next == MAP_FAILED)
            return(NULL);
        t_mem* mem_tmp = ft_data;
        ft_data = ft_data->next;
        ft_data->prev = mem_tmp;
        ft_data->size = mem_size;
        ft_data->next = NULL;
    }

    i += MEM_METADATA_SIZE;
    t_mem *mem_ptr = ft_data;

    mem_ptr->first_alloc = (t_alloc*)((char*)mem_ptr + i);
    i += ALLOC_METADATA_SIZE;
    t_alloc* alloc_ptr = mem_ptr->first_alloc;
    alloc_ptr->prev = NULL;
    alloc_ptr->next = NULL;
    alloc_ptr->is_free = false;
    alloc_ptr->size = alloc_size - ALLOC_METADATA_SIZE + 15;
    alloc_ptr->allocated_size = size;
    alloc_ptr->ptr = (void*)(((uintptr_t)(mem_ptr + i) + 15) & ~ (uintptr_t)0x0F);
    // ft_bzero(alloc_ptr->ptr, ALLOC_METADATA_SIZE);
    i += alloc_size - ALLOC_METADATA_SIZE + 15;
    void* ret_ptr = alloc_ptr->ptr;

    while ((i + alloc_size) < mem_size) {
        alloc_ptr->next = (t_alloc*)((char*)mem_ptr + i);
        i += ALLOC_METADATA_SIZE;
        alloc_ptr->next->prev = alloc_ptr;
        alloc_ptr = alloc_ptr->next;
        alloc_ptr->is_free = true;
        alloc_ptr->ptr = (void*)(((uintptr_t)(mem_ptr + i) + 15) & ~ (uintptr_t)0x0F);
        // ft_bzero(alloc_ptr->ptr, ALLOC_METADATA_SIZE);
        alloc_ptr->size = alloc_size - ALLOC_METADATA_SIZE - 15;
        alloc_ptr->next = NULL;
        i += alloc_size - ALLOC_METADATA_SIZE + 15;
    }
    mem_ptr->used_allocations = 1;

    while (alloc_ptr->prev != NULL){
        alloc_ptr = alloc_ptr->prev;
    }
    while (ft_data->prev != NULL){
        ft_data = ft_data->prev;
    }
    return (ret_ptr);
}

void *malloc(size_t size)
{
    void *ptr = NULL;

    size_t max_stack_size = maxStackSize();
    if (size > max_stack_size)
        size = max_stack_size;
    ptr = search_available_mem_segment(size);
    if (ptr == NULL){
        ptr = create_new_mem_segment(size);
    }
    // show_alloc_mem();
    return (ptr);
}

