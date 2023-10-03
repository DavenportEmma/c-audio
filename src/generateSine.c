#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "generateSine.h"
#include "sig_descriptor.h"

int16_t* generateSine(
    SigDescriptor s    
) {
    int16_t* d = (int16_t*)malloc(s.samples * sizeof(int16_t));

    for(int i=0; i<s.samples; i++) {
        double x = 2*PI*i/(s.sample_rate/s.freq);
        double sample_val = sin(x);

        double A_sample_float = (double)sample_val*s.gain;
        int16_t A_sample = (int16_t)A_sample_float + s.offset;

        d[i] = A_sample;
    }

    return d;
}