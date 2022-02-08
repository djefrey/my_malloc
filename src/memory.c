/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-jeffrey.winkler
** File description:
** memory
*/

#include <unistd.h>
#include "my_malloc.h"

void *extend_heap(size_t req_size)
{
    size_t min_size = 2 * getpagesize();
    size_t incr = 0;
    void *new_brk = (void*) -1;

    for (; incr < req_size; incr += min_size);
    new_brk = sbrk(incr);
    return new_brk == (void*) -1 ? NULL : new_brk;
}

void write_new_block_data(block_t *block, size_t size)
{
    block->size = size;
    block->next = NULL;
    block->ptr = ((void*) block) + BLOCK_SIZE;
    block->free = 0;
}
