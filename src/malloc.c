/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-jeffrey.winkler
** File description:
** malloc
*/

#include <unistd.h>
#include <string.h>
#include "my_malloc.h"
#include "debug.h"

#include <stdio.h>

void *malloc(size_t size)
{
    static void *base = NULL;
    static block_t *last = NULL;
    size_t aligned_size = ALIGN4(size);
    block_t *block;
    block_t *new;

    #if DEBUG
        debug_print_str("\nMalloc:\nSize:");
        debug_print_size(size);
        debug_print_str("Aligned size:");
        debug_print_size(aligned_size);
        debug_print_str("\n");
    #endif
    if (size == 0)
        return NULL;
    if (aligned_size < MIN_ALLOC)
        aligned_size = MIN_ALLOC;
    if (base) {
        #if DEBUG
            debug_print_str("Malloc: Base already set");
        #endif
        new = search_append_split(base, aligned_size, last);
        if (!new)
            return NULL;
        last = new;
        return ((void*) new) + BLOCK_SIZE;
    } else {
        #if DEBUG
            debug_print_str("First call to malloc\n");
        #endif
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
    #if DEBUG
        debug_print_str("Free");
    #endif
    block = ptr - BLOCK_SIZE;
    if (block->ptr == ptr)
        block->free = 1;
    else {
        #if DEBUG
            debug_print_str("Invalid free !");
        #endif
    }
}

void *calloc(size_t nmemb, size_t size)
{
    void *ptr = NULL;
    size_t total = 0;

    #if DEBUG
        debug_print_str("\nCalloc");
    #endif
    if (nmemb == 0 || size == 0)
        return NULL;
    total = nmemb * size;
    if (total / nmemb != size)
        return NULL;
    ptr = malloc(nmemb * size);
    memset(ptr, 0, total);
    return ptr;
}

void *realloc(void *ptr, size_t size)
{
    block_t *block = ptr - BLOCK_SIZE;
    void *new = NULL;

    #if DEBUG
        debug_print_str("\nRealloc");
    #endif
    if (!ptr)
        return (malloc(size));
    else if (block->ptr != ptr)
        return (NULL);
    if (size < block->size)
        return (((void*) split_existing_block(block, size)) + BLOCK_SIZE);
    else if (size > block->size) {
        merge_blocks(block);
        if (size <= block->size)
            return (((void*) block) + BLOCK_SIZE);
        if (!(new = malloc(size)))
            return NULL;
        memcpy(new, ptr, block->size);
        block->free = 1;
        return new;
    }
    return ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    size_t total = 0;

    #if DEBUG
        debug_print_str("\nReallocarray");
    #endif
    if (nmemb == 0 || size == 0)
        return NULL;
    total = nmemb * size;
    if (total / nmemb != size)
        return NULL;
    return realloc(ptr, total);
}