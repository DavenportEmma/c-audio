#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "generateSine.h"

int16_t* generateSine(int sample_rate, int freq, int samples, int16_t gain) {
    int16_t* d = (int16_t*)malloc(samples * sizeof(int16_t));

    for(int i=0; i<samples; i++) {
        double x = 2*PI*i/(sample_rate/freq);
        double sample_val = sin(x);

        double A_sample_float = (double)sample_val*gain;
        int16_t A_sample = (int16_t)A_sample_float;

        d[i] = A_sample;
    }

    return d;
}