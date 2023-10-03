#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "wav_header.h"
#include "writeWav.h"
#include "writeCSV.h"
#include "sig_descriptor.h"
#include "generateSignals.h"
#include "filter.h"
#define NUM_SIGS 1

int main(int argc, char** argv) {
    int samples = 1000;
    short int num_channels = 1;
    int sample_rate = 44100;
    short int bits_per_sample = 16;
    int byte_rate = sample_rate * bits_per_sample * num_channels / 8;
    short int bytes_per_sample = bits_per_sample / 8; // 2 for 16b mono

    /*
        sample rate
        freq
        samples
        gain
        offset
        phase
    */
    SigDescriptor arr[NUM_SIGS] = {
        {
            sample_rate,
            100,
            samples,
            10000,
            0,
            0,
            SQUARE
        }
    };

    WavHeader h = {
        "RIFF",
        36,
        "WAVE",
        "fmt\x20", //  \x20 represents the end of header
        16,
        1,
        num_channels,
        sample_rate,
        byte_rate,
        bytes_per_sample,
        bits_per_sample,
        "data",
        samples * bytes_per_sample
    };

    char* file_name = "out/a.out.wav";

    int16_t* dt = (int16_t*)malloc(samples * sizeof(int16_t));

    generateSignals(h, arr, NUM_SIGS, dt);
    writeCSV("out/a.txt", dt, samples);
    float a_coeff[3] = {-0.6320, 2.1848, -2.5430};
    float b_coeff[4] = {1,3,3,1};
    filter(a_coeff, 3, b_coeff, 4, dt, samples);

    int flag = writeWav(h, file_name, dt, samples);

    free(dt);

    return 0;
}