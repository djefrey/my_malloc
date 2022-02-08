/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-jeffrey.winkler
** File description:
** block
*/

#include <unistd.h>
#include "my_malloc.h"

block_t *allocate_and_setup_block(void *ptr, size_t size)
{
    block_t *block = ptr;

    if (!extend_heap(BLOCK_SIZE + size))
        return (NULL);
    write_new_block_data(block, size);
    return (ptr);
}

block_t *append_new_block(block_t *last, size_t size)
{
    void *ptr = last + BLOCK_SIZE + last->size;
    void *brk = sbrk(0);

    if (ptr + BLOCK_SIZE + size >= brk) {
        if (!extend_heap(size + BLOCK_SIZE))
            return (NULL);
    }
    write_new_block_data(ptr, size);
    last->next = ptr;
    return (ptr);
}

block_t *split_existing_block(block_t *block, size_t size)
{
    void *end = block + BLOCK_SIZE + block->size;
    size_t diff = block->size - size;
    block_t *next;

    if (diff > BLOCK_SIZE + MIN_ALLOC) {
        next = block + BLOCK_SIZE + size;
        next->size = (void*) next + BLOCK_SIZE - end;
        next->next = block->next;
        next->free = 1;
        block->size = size;
        block->next = next;
    }
    block->free = 0;
    return block;
}

block_t *merge_blocks(block_t *block)
{
    size_t total_size = block->size;
    block_t *next = block->next;

    for (; next && next->free; next = next->next)
        total_size += next->size;
    block->size = total_size;
    block->next = next;
    return (block);
}