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
    t_mem *mem_ptr = &ft_data;
    void *ret_ptr = NULL;
    size_t i = 0;
    size_t mem_size = which_mem_size(size);
    size_t alloc_size = which_alloc_size(size);
    (void)alloc_size;

    void* ptr;
    ptr = mmap(NULL, mem_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem_ptr->next == MAP_FAILED)
        return (write(1, "Error: mmap failed\n", 19), NULL);

    if (mem_ptr->next == NULL) {
        mem_ptr = (t_mem*)ptr;
        mem_ptr->prev = NULL;
    } else {
        while (mem_ptr->next != NULL) 
            mem_ptr = mem_ptr->next;
        mem_ptr->next = (t_mem*)ptr;
        mem_ptr->next->prev = mem_ptr;
        mem_ptr = mem_ptr->next;
    }
    mem_ptr->size = mem_size;
    mem_ptr->next = NULL;
    i += MEM_METADATA_SIZE;

    mem_ptr->first_alloc = (t_alloc*)((char*)(ptr + i));
    i += ALLOC_METADATA_SIZE;
    t_alloc* alloc_ptr = mem_ptr->first_alloc;
    alloc_ptr->prev = NULL;
    alloc_ptr->next = NULL;
    alloc_ptr->is_free = true;
    alloc_ptr->size = alloc_size;
    alloc_ptr->ptr = (void*)((char*)(ptr + i));
    i += TINY_ALLOC_SPACE;
    ret_ptr = alloc_ptr->ptr;

    size_t j = 1;
    while (i < mem_size) {
        alloc_ptr->next = (t_alloc*)((char*)ptr + i);
        i += ALLOC_METADATA_SIZE;
        alloc_ptr->next->prev = alloc_ptr;
        alloc_ptr = alloc_ptr->next;
        alloc_ptr->is_free = true;
        alloc_ptr->ptr = ((char*)ptr + i);
        alloc_ptr->size = alloc_size;
        alloc_ptr->next = NULL;
        i += TINY_ALLOC_SPACE;
        ++j;
    }
    write(1, "i: ", 3);
    ft_putnbr_fd(i, 1);
    write(1, "\n", 1);
    write(1, "mem_size: ", 10);
    ft_putnbr_fd(mem_size, 1);
    write(1, "\n", 1);
    write(1, "j: ", 3);
    ft_putnbr_fd(j, 1);
    write(1, "\n", 1);

    // while (++i < 126) // if 128, corruption warning at exec 
    // {
    //     j += alloc_size;
    //     alloc_ptr->next = (t_alloc*)((char*)alloc_ptr + alloc_size);
    //     alloc_ptr->next->prev = alloc_ptr;
    //     alloc_ptr = alloc_ptr->next;
    //     alloc_ptr->ptr = ((char*)alloc_ptr + ALLOC_METADATA_SIZE);
    //     alloc_ptr->is_free = true;
    //     alloc_ptr->next = NULL;
    // }
    // while (alloc_ptr->prev != NULL){
    //     alloc_ptr = alloc_ptr->prev;
    // }
    // while (mem_ptr->prev != NULL){
    //     mem_ptr = mem_ptr->prev;
    // }
    return (ret_ptr);
}

void *malloc(size_t size)
{
    void *ptr = NULL;
    // unsigned char* ptr = (unsigned char*)mmap(NULL, 10, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    // ptr = (unsigned char*)ptr;
    // ptr[0] = 'c';
    // (void)ptr;
    // write (1, ptr, 1);

    // ptr = search_available_mem_segment(size);
    // if (0) {
        if (ptr == NULL){
            ptr = create_new_mem_segment(size);
        }
        show_alloc_mem();
    // }

    return (NULL);
}

