#ifndef FILTER_H
#define FILTER_H

#include <stdint.h>

void filter(
    double a[],
    double b[],
    int16_t* buffer,
    int buffer_len,
    int16_t* filtered
);

#endif