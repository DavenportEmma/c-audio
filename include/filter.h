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
    double a[],
    int a_len,
    double b[],
    int b_len,
    int16_t* buffer,
    int buffer_len,
    int16_t* filtered
);

#endif