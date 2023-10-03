#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "generateSignal.h"
#include "sig_descriptor.h"
#include "wav_header.h"

void generateSignals(
    WavHeader h,
    SigDescriptor s[],
    int num,
    int16_t* buffer    
) {
    int num_samples = s[0].samples;

    for(int i=0; i<num_samples; i++) {
        buffer[i] = 0;
    }

    int16_t* d = (int16_t*)malloc(num_samples * sizeof(int16_t));

    for(int i=0; i<num; i++) {
        generateSignal(s[i], d);

        for(int j=0; j<num_samples; j++) {
            buffer[j] = buffer[j]+ d[j];
        }
    }

    free(d);
}
