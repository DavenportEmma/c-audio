#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "readWav.h"
#include "wav_header.h"
#include "generateSignal.h"
#include "writeWav.h"
#include "writeCSV.h"
#include "filter.h"

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
    int16_t* filtered = (int16_t*)malloc(h->data_len);
    extractAudioData("audio/AM.wav", buffer, samples);

    for(int i = 0; i < samples; i++) {
        if(buffer[i] < 0) {
            buffer[i] = abs(buffer[i]);
        }
    }

    double a_coeff[3] = {1, -1.95557824, 0.95654368};
    double b_coeff[3] = {0.00024136, 0.00048272, 0.00024136};

    filter(
        a_coeff,
        b_coeff,
        buffer,
        samples,
        filtered
    );

    float* env_norm = (float*)malloc(samples * sizeof(float));
    float max_signed = pow(2, h->bits_per_sample) / 2;

    
    for(int i = 0; i < samples; i++) {
        float f = (float)filtered[i];
        env_norm[i] = f/max_signed;

    }

    extractAudioData("audio/sin.wav", buffer, samples);
    
    FILE *fp;
    fp = fopen("build-envelope-detection/a.txt", "wb");
    for(int i = 0; i < samples; i++) {
        buffer[i] = buffer[i] * env_norm[i];
        fprintf(fp, "%i\n", buffer[i]);
    }

    fclose(fp);


    printf("Finished\n");

    free(filtered);
    free(h);
    free(buffer);
    free(env_norm);
    return 0;
}