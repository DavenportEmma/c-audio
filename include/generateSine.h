#ifndef GENERATE_SINE_H
#define GENERATE_SINE_H

#include <stdint.h>
#include "sig_descriptor.h"
#define PI 3.14159265

void generateSine(
    SigDescriptor s,
    int16_t *buffer
);

#endif