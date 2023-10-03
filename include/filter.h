#ifndef FILTER_H
#define FILTER_H

#include <stdint.h>

void filter(
    float x[],
    int x_len,
    float y[],
    int y_len,
    int16_t* buffer
);

#endif