#ifndef FILTER_DESCRIPTOR_H
#define FILTER_DESCRIPTOR_H

#include "config.h"

typedef struct {
    float a[A_LEN];
    float b[B_LEN];
} FilterDescriptor;

typedef struct {
    float y[A_LEN];
    float x[B_LEN];
} FilterBuffer;

#endif