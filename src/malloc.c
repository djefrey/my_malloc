/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-jeffrey.winkler
** File description:
** malloc
*/

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "my_malloc.h"
#include "debug.h"

void *malloc(size_t size)
{
    static void *base = NULL;
    size_t aligned_size = ALIGN4(size);
    block_t *block;
    block_t *new;

    if (size == 0)
        return NULL;
    if (aligned_size < MIN_ALLOC)
        aligned_size = MIN_ALLOC;
    if (base) {
        new = search_append_split(base, aligned_size);
        if (!new)
            return NULL;
        return ((void*) new) + BLOCK_SIZE;
    } else {
        base = sbrk(0);
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

void *calloc(size_t nmemb, size_t size)
{
    void *ptr = NULL;
    size_t total = 0;

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

    if (!ptr)
        return (malloc(size));
    else if (block->ptr != ptr)
        return (NULL);
    if (size == 0) {
        block->free = 1;
        return NULL;
    }
    if (size < block->size)
        return (((void*) split_existing_block(block, size)) + BLOCK_SIZE);
    else if (size > block->size) {
        merge_blocks(block);
        if (size <= block->size)
            return (((void*) split_existing_block(block, size)) + BLOCK_SIZE);
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

    if (nmemb == 0 || size == 0) {
        if (ptr)
            free(ptr);
        return NULL;
    }
    total = nmemb * size;
    if (total / nmemb != size) {
        errno = ENOMEM;
        return NULL;
    }
    return realloc(ptr, total);
}