/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-jeffrey.winkler
** File description:
** best_fit
*/

#include <stdio.h>
#include <unistd.h>
#include "my_malloc.h"
#include "debug.h"

static void check_if_is_better(block_t *block, block_t **best, size_t size)
{
    #if INFO
        debug_print_str("Check if better");
    #endif
    if (block->size < size)
        return;
    if (*best == NULL)
        *best = block;
    else if (block->size < (*best)->size)
        *best = block;
}

block_t *find_best_block(block_t *base, size_t size)
{
    block_t *block = base;
    block_t *prev = NULL;
    block_t *best = NULL;
    int prev_is_free = 0;

    #if INFO
        debug_print_str("Find best block");
    #endif
    for (; block; prev = block, block = block->next) {
        if (!block->free) {
            prev_is_free = 0;
        } else {
            if (prev_is_free) {
                #if TOO_MUCH_LOG
                    debug_print_str("Prev is free, merging blocks");
                #endif
                merge_blocks(prev);
                block = prev;
            }
            check_if_is_better(block, &best, size);
            prev_is_free = 1;
        }
    }
    #if LOG
        debug_print_str("Best block is:");
        debug_print_ptr(best);
    #endif
    return (best);
}

block_t *get_last_block(block_t *start)
{
    block_t *last = start;

    for (; last->next; last = last->next) {
        #if TOO_MUCH_LOG
            debug_print_str("--Last--");
            debug_print_ptr(last);
            debug_print_ptr(last->ptr);
            debug_print_size(last->size);
            debug_print_size((size_t) last->free);
        #endif
    }
    return last;
}