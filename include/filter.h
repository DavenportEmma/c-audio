#ifndef FILTER_H
#define FILTER_H

#include <stdint.h>

void filter(
    float a[],
    int a_len,
    float b[],
    int b_len,
    int16_t* buffer
    int buffer_len
);

#endif