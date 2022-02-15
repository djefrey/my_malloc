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
    if (block->size >= size) {
        if (*best == NULL)
            *best = block;
        else if (block->size < (*best)->size)
            *best = block;
    }
}

block_t *find_best_block(block_t *base, size_t size)
{
    block_t *block = base;
    block_t *best = NULL;

    for (; block; block = block->next) {
        if (block->free)
            check_if_is_better(block, &best, size);
    }
    return (best);
}

block_t *get_last_block(block_t *start)
{
    block_t *last = start;

    for (; last->next; last = last->next);
    return last;
}