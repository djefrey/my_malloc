/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-jeffrey.winkler
** File description:
** malloc
*/

#pragma once

#include <stddef.h>

#define BLOCK_SIZE (sizeof(block_t))
#define MIN_ALLOC ((size_t) 16)

typedef struct block_s {
    size_t size;
    void *next;
    void *ptr;
    int free;
} block_t;

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

block_t *search_append_split(void *base, size_t size);
void *extend_heap(size_t req_size);
void write_new_block_data(block_t *block, size_t size);

block_t *allocate_and_setup_block(void *ptr, size_t size);
block_t *append_new_block(block_t *last, size_t size);
block_t *split_existing_block(block_t *block, size_t size);
block_t *merge_blocks(block_t *block);

block_t *find_best_block(block_t *base, size_t size);
block_t *get_last_block(block_t *start);

size_t min(size_t a, size_t min);
size_t align4(size_t size);