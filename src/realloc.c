/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-jeffrey.winkler
** File description:
** realloc
*/

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "my_malloc.h"
#include "debug.h"

static int realloc_basic_checks(void **ptr, block_t *block, size_t size)
{
    if (!(*ptr)) {
        *ptr = malloc(size);
        return 1;
    } else if (block->ptr != *ptr) {
        *ptr = NULL;
        return 1;
    }
    if (size == 0) {
        block->free = 1;
        *ptr = NULL;
        return 1;
    }
    return 0;
}

static void *realloc_increase_alloc(void *ptr, block_t *block, size_t size)
{
    size_t ori_size = block->size;
    block_t *new_block = NULL;
    void *new_ptr = NULL;

    merge_blocks(block);
    if (size <= block->size) {
        new_block = split_existing_block(block, size);
        new_ptr = ((void*) new_block) + BLOCK_SIZE;
    } else {
        block->free = 1;
        if (!(new_ptr = malloc(size))) {
            block->free = 0;
            return NULL;
        }
        memcpy(new_ptr, ptr, ori_size);
    }
    return new_ptr;
}

void *realloc(void *ptr, size_t size)
{
    block_t *block = ptr - BLOCK_SIZE;

    if (realloc_basic_checks(&ptr, block, size))
        return ptr;
    if (size < block->size)
        return (((void*) split_existing_block(block, size)) + BLOCK_SIZE);
    else if (size > block->size)
        return realloc_increase_alloc(ptr, block, size);
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