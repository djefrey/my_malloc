/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-jeffrey.winkler
** File description:
** debug
*/

#pragma once

#include <stddef.h>

#define INFO (DEBUG)
#define LOG 0
#define TOO_MUCH_LOG 0

#define DEBUG 1

typedef struct block_s block_t;

void debug_print_ptr(void *ptr);
void debug_print_size(size_t size);
void debug_print_str(const char *str);
void debug_print_total_heap(void *base, block_t *last);
