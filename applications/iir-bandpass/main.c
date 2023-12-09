#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "wav_header.h"
#include "writeWav.h"
#include "writeCSV.h"
#include "sig_descriptor.h"
#include "generateSignals.h"
#include "filter.h"
#define NUM_SIGS 4

int main(int argc, char** argv) {
    int samples = 10000;
    short int num_channels = 1;
    int sample_rate = 10000;
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
            1000,
            0,
            0,
            SINE
        },
        {
            sample_rate,
            500,
            samples,
            1000,
            0,
            0,
            SINE
        },
        {
            sample_rate,
            2000,
            samples,
            1000,
            0,
            0,
            SINE
        },
        {
            sample_rate,
            5000,
            samples,
            1000,
            0,
            0,
            SINE
        },
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
    int16_t* filtered = (int16_t*)malloc(samples * sizeof(int16_t));

    generateSignals(h, arr, NUM_SIGS, dt);
    writeCSV("out/a.txt", dt, samples);
    double a_coeff[3] = {0.07069445632248525, 0, -0.07069445632248525};
    double b_coeff[4] = {1, -0.5743424119264041, 0.8586110873550294, 0};
    filter(a_coeff, 3, b_coeff, 4, dt, samples, filtered);

    int flag = writeWav(h, file_name, filtered, samples);
    flag = writeWav(h, "out/unfiltered.wav", dt, samples);

    free(dt);
    free(filtered);
    return 0;
}