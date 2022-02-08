/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-jeffrey.winkler
** File description:
** malloc
*/

#include <unistd.h>
#include "my_malloc.h"

#include <stdio.h>

void *malloc(size_t size)
{
    static void *base = NULL;
    static block_t *last = NULL;
    size_t aligned_size = ALIGN4(size);
    block_t *block;
    block_t *new;

    if (size == 0)
        return NULL;
    if (aligned_size < MIN_ALLOC)
        aligned_size = MIN_ALLOC;
    if (base) {
        block = find_best_block(base, aligned_size);
        if (!block)
            new = append_new_block(last, aligned_size);
        else
            new = split_existing_block(block, aligned_size);
        if (!new)
            return (NULL);
        last = new;
        return ((void*) new) + BLOCK_SIZE;
    } else {
        base = sbrk(0);
        last = base;
        block = allocate_and_setup_block(base, aligned_size);
        return ((void*) block) + BLOCK_SIZE;
    }
    return NULL;
}

void free(void *ptr)
{
    block_t *block;

    if (!ptr)
        return;
    block = ptr - BLOCK_SIZE;
    if (block->ptr == ptr)
        block->free = 1;
}