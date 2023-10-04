#ifndef FILTER_H
#define FILTER_H

#include <stdint.h>

#define A_COEFFS 4
#define B_COEFFS 4

typedef struct {
    float a[A_COEFFS];
    float b[B_COEFFS];
} FilterDescriptor;

void filter(
    FilterDescriptor f,
    int16_t* buffer,
    int buffer_len
);

#endif