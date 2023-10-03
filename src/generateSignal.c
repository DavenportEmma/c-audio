#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "generateSignal.h"
#include "sig_descriptor.h"

double sgn(double sin_val) {
    if(sin_val > 0) return 1;
    if(sin_val < 0) return -1;
    return 0;
}

void generateSignal(
    SigDescriptor s,
    int16_t* buffer    
) {
    for(int i=0; i<s.samples; i++) {
        double x = 2*PI*(i+s.phase)/(s.sample_rate/s.freq);
        double sample_val;

        switch (s.type)
        {
        case SINE:
            sample_val = sin(x);
            break;
        case SQUARE:
            sample_val = sgn(sin(x));
            break;
        default:
            sample_val = sin(x);
            break;
        }

        double A_sample_float = (double)sample_val*s.gain;
        int16_t A_sample = (int16_t)A_sample_float + s.offset;

        buffer[i] = A_sample;
    }
}
