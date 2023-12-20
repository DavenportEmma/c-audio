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
    int samples = h->data_len / h->total_bytes_per_sample;

    int16_t* buffer = (int16_t*)malloc(h->data_len);

    extractAudioData("audio/AM.wav", buffer, samples);

    double bps = h->bits_per_sample;
    double max_signed = pow(2, bps) / 2;

    FILE *fp;
    fp = fopen("build-envelope-detection/a.txt", "wb");

    if (fp == NULL) {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    float* f_buffer = (float*)malloc(h->data_len);

    for(int i = 0; i < samples; i++) {
        float v = (float)buffer[i];
        if(v < 0) {
            v = v * -1;
        }

        float v_norm = v/max_signed;
        f_buffer[i] = v_norm;
    }
    fclose(fp);
    
    

    free(h);
    free(f_buffer);
    free(buffer);
    return 0;
}