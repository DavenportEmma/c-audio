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
    fclose(fp);
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

    int flag = fread(h, sizeof(WavHeader), 1, fp);
    printf("%i\n", ferror(fp));
    flag = fread(buffer, sizeof(int8_t), buffer_len, fp);
    printf("%i\n", ferror(fp));


    if(ferror(fp)) {
        printf("ferror %i\n", ferror(fp));
    }

    if(feof(fp)) {
        printf("eof\n");
    } else {
        printf("not eof\n");
    }

    fclose(fp);
    return 0;
}