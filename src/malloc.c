/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-jeffrey.winkler
** File description:
** malloc
*/

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/param.h>
#include "my_malloc.h"

void *malloc(size_t size)
{
    static void *base = NULL;
    size_t aligned_size = min(align4(size), MIN_ALLOC);
    block_t *block;
    block_t *new;

    if (size == 0)
        return NULL;
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
