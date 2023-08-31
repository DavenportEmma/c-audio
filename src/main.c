#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "wav_header.h"
#include "writeWav.h"

int main(int argc, char** argv) {
    WavHeader h = {
        "RIFF",
        36,
        "WAVE",
        "fmt\x20", //  \x20 represents the end of header
        16,
        1,
        1,
        44100,
        88200,
        2,
        16,
        "data",
        100
    };

    char* file_name = "out/a.out.wav";

    int data_len = 100;

    int16_t* d = (int16_t*)malloc(data_len * sizeof(int16_t));

    for(int i=0; i<data_len; i++) {
        d[i] = 0x8FFF;
    }

    int flag = flag = writeWav(h, file_name, d, data_len);

    free(d);

    return 0;
}