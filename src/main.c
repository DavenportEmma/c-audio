#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "wav_header.h"
#include "writeWav.h"
#include "generateSine.h"
#include "writeCSV.h"
#include "sig_descriptor.h"
#include "generateSignals.h"

int main(int argc, char** argv) {
    int samples = 44100;
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
    SigDescriptor arr[3] = {
        {
            sample_rate,
            220,
            samples,
            5000,
            0,
            0
        },
        {
            sample_rate,
            330,
            samples,
            5000,
            0,
            0
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
    generateSignals(h, arr, 3, dt);

    int flag = writeWav(h, file_name, dt, samples);

    free(dt);

    return 0;
}