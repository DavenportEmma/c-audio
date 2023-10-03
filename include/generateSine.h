#ifndef GENERATE_SINE_H
#define GENERATE_SINE_H

#include <stdint.h>

#define PI 3.14159265

int16_t* generateSine(
    int sample_rate,
    int freq,
    int samples,
    int16_t gain
);

#endif