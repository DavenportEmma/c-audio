#include <stdio.h>
#include <stdlib.h>

#include "readWav.h"
#include "wav_header.h"
#include "writeCSV.h"

int getMetadata(char* file_name, WavHeader* h) {
    FILE *fp;
    fp = fopen(file_name, "rb");

    if(fp == NULL) {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    fread(h, sizeof(WavHeader), 1, fp);
    return 0;
}

int extractAudioData(
    char* file_name, WavHeader* h, int8_t* buffer, int buffer_len
) {
    FILE *fp;
    fp = fopen("audio/AM.wav", "rb");

    if(fp == NULL) {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    fread(h, sizeof(WavHeader), 1, fp);
    fread(buffer, sizeof(int8_t), buffer_len, fp);

    return 0;
}