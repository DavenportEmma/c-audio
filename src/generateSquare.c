#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "generateSquare.h"
#include "sig_descriptor.h"

double sgn(double sin_val) {
    if(sin_val > 0) return 1;
    if(sin_val < 0) return -1;
    return 0;
}

void generateSquare(
    SigDescriptor s,
    int16_t *buffer   
) {
    for(int i=0; i<s.samples; i++) {
        double x = 2*PI*(i+s.phase)/(s.sample_rate/s.freq);
        
        double sample_val = sgn(sin(x));

        double A_sample_float = (double)sample_val*s.gain;
        int16_t A_sample = (int16_t)A_sample_float + s.offset;

        buffer[i] = A_sample;
    }
}