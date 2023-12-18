#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "readWav.h"
#include "wav_header.h"
#include "generateSignal.h"
#include "writeWav.h"
#include "writeCSV.h"

int main(int argc, char** argv) {
    /*
        how to get envelope
        1. abs on signal
        2. apply low pass (Fc ~10Hz)
        3. BAM
    */

    WavHeader *h = (WavHeader*)malloc(sizeof(WavHeader));

    int flag = getMetadata("audio/AM.wav", h);

    uint8_t* buffer = (uint8_t*)malloc(h->data_len);
    float* f_buffer = (float*)malloc(h->data_len);

    extractAudioData("audio/AM.wav", h, buffer, h->data_len);

    // uint8_t max = (uint8_t)pow(2, h->bits_per_sample);
    // double _halfway = pow(2, h->bits_per_sample) / 2;
    // uint8_t halfway = (uint8_t)_halfway;

    for(int i = 0; i < h->data_len; i++) {
    //     uint8_t v;
    //     if(buffer[i] >= halfway) {
    //         v = buffer[i] - halfway;
    //     } else {
    //         v = max - buffer[i] - halfway;
    //     }

    //     buffer[i] = v;
        // printf("%d\n", buffer[i]);
        // f_buffer[i] = halfway / buffer[i];
        // float f = (float)buffer[i] / (float)halfway;
        // printf("%f = %i / %i\n", f, buffer[i], halfway);
    }

    writeCSV_uint8("build-envelope-detection/a.txt", buffer, h->data_len);
    
    free(h);
    free(buffer);
    free(f_buffer);
    return 0;
}