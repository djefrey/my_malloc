/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-jeffrey.winkler
** File description:
** block
*/

#include <unistd.h>
#include "my_malloc.h"
#include "debug.h"

block_t *allocate_and_setup_block(void *ptr, size_t size)
{
    block_t *block = ptr;

    #if DEBUG
        debug_print_str("Allocate and setup block:\nSize:");
        debug_print_size(size);
    #endif
    if (!extend_heap(BLOCK_SIZE + size))
        return NULL;
    write_new_block_data(block, size);
    return ptr;
}

block_t *append_new_block(block_t *last, size_t size)
{
    void *ptr = ((void*) last) + BLOCK_SIZE + last->size;
    void *brk = sbrk(0);

    #if DEBUG
        debug_print_str("Append new block\nSize:");
        debug_print_size(size);
    #endif
    if (ptr + BLOCK_SIZE + size >= brk) {
        #if DEBUG
            debug_print_str("Append: New block is too big ! Extending heap...");
        #endif
        if (!extend_heap(size + BLOCK_SIZE))
            return NULL;
    }
    write_new_block_data(ptr, size);
    last->next = ptr;
    return ptr;
}

block_t *split_existing_block(block_t *block, size_t size)
{
    void *end = ((void*) block) + BLOCK_SIZE + block->size;
    size_t diff = block->size - size;
    block_t *next;

    #if DEBUG
        debug_print_ptr("Spliting existing block\nBlock size:");
        debug_print_size(block->size);
        debug_print_str("New size:");
        debug_print_size(size);
    #endif
    if (diff > BLOCK_SIZE + MIN_ALLOC) {
        #if DEBUG
            debug_print_str("Split: More space availaible than the minimum. Splitting...");
        #endif
        next = ((void*) block) + BLOCK_SIZE + size;
        next->size = end - ((void*) next) + BLOCK_SIZE;
        next->ptr = ((void*) next) + BLOCK_SIZE;
        next->next = block->next;
        next->free = 1;
        block->size = size;
        block->next = next;
        #if DEBUG
            debug_print_str("Spliting succeed");
        #endif
    }
    block->free = 0;
    return block;
}

block_t *merge_blocks(block_t *block)
{
    size_t total_size = block->size;
    block_t *next = block->next;

    #if DEBUG
        debug_print_str("Merging blocks...");
    #endif
    for (; next && next->free; next = next->next)
        total_size += next->size;
    #if DEBUG
        debug_print_str("Merge: prev size:");
        debug_print_size(block->size);
        debug_print_str("New size:");
        debug_print_size(total_size);
    #endif
    block->size = total_size;
    block->next = next;
    return block;
}