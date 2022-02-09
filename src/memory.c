/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-jeffrey.winkler
** File description:
** memory
*/

#include <unistd.h>
#include "my_malloc.h"
#include "debug.h"

block_t *search_append_split(void *base, size_t size)
{
    block_t *block = find_best_block(base, size);
    block_t *last = NULL;
    block_t *result = NULL;

    if (!block) {
        #if INFO
            debug_print_str("Append new block");
        #endif
        last = get_last_block(base);
        result = append_new_block(last, size);
    } else {
        #if INFO
            debug_print_str("Split existing block");
        #endif
        result = split_existing_block(block, size);
    }
    return result;
}

void *extend_heap(size_t req_size)
{
    size_t min_size = 2 * getpagesize();
    size_t incr = 0;
    void *new_brk = (void*) -1;

    #if INFO
        debug_print_str("Increase heap:");
        debug_print_size(req_size);
    #endif
    for (; incr < req_size; incr += min_size);
    new_brk = sbrk(incr);
    #if INFO
        debug_print_str("Incease heap of:");
        debug_print_size(incr);
        if (new_brk == (void*) -1)
            debug_print_str("Failed to increase heap !");
    #endif
    return new_brk == (void*) -1 ? NULL : new_brk;
}

void write_new_block_data(block_t *block, size_t size)
{
    #if INFO
        debug_print_str("Writring new block data");
    #endif
    block->size = size;
    block->next = NULL;
    block->ptr = ((void*) block) + BLOCK_SIZE;
    block->free = 0;
    #if INFO
        debug_print_str("Succeed to write new block data");
    #endif
}
