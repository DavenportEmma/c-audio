#ifndef FILTER_H
#define FILTER_H

#include <stdint.h>

#define A_COEFFS 4
#define B_COEFFS 4

typedef struct {
    double a[A_COEFFS];
    double b[B_COEFFS];
} FilterDescriptor;

void filter(
    FilterDescriptor f,
    int16_t* input,
    int16_t* output,
    int buffer_len
);

#endif