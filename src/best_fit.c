/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-jeffrey.winkler
** File description:
** best_fit
*/

#include <unistd.h>
#include "my_malloc.h"

static void check_if_is_better(block_t *block, block_t **best, size_t size)
{
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

    for (; block != NULL; prev = block, block = block->next) {
        if (!block->free) {
            prev_is_free = 0;
        } else {
            if (prev_is_free) {
                merge_blocks(prev);
                block = prev;
            }
            check_if_is_better(block, &best, size);
        }
    }
    return (best);
}