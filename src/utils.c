/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-jeffrey.winkler
** File description:
** utils
*/

#include <stddef.h>

size_t min(size_t a, size_t min)
{
    return a < min ? min : a;
}

size_t align4(size_t size)
{
    return ((size - 1 >> 2) << 2) + 4;
}