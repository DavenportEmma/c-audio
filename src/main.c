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
            6000,
            samples,
            5000,
            0,
            0,
            SINE
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

    FilterDescriptor f = {
        {-0.9461929090407919, 1, 0, 0},
        {1, 1, 0, 0}
    };

    int16_t* dt = (int16_t*)malloc(samples * sizeof(int16_t));
    int16_t* filter_out = (int16_t*)malloc(samples * sizeof(int16_t));

    generateSignals(h, arr, NUM_SIGS, dt);
    filter(f, dt, filter_out, samples);

    int flag = writeWav(h, "out/a.wav", dt, samples);
    flag = writeWav(h, "out/f.wav", filter_out, samples);

    free(dt);
    free(filter_out);

    return 0;
}