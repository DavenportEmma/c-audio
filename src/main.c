#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "wav_header.h"
#include "writeWav.h"

int main(int argc, char** argv) {
    int samples = 100;
    int sample_rate = 44100;
    short int num_channels = 1;
    short int bits_per_sample = 16;
    int byte_rate = sample_rate * bits_per_sample * num_channels / 8;
    short int bytes_per_sample = bits_per_sample / 8; // 2 for 16b mono

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
        samples
    };

    char* file_name = "out/a.out.wav";

    int16_t* d = (int16_t*)malloc(samples * sizeof(int16_t));

    for(int i=0; i<samples; i++) {
        d[i] = 0x8FFF;
    }

    int flag = flag = writeWav(h, file_name, d, samples);

    free(d);

    return 0;
}