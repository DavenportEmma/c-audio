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
    char* file_name, int16_t* buffer, int samples
) {
    FILE *fp;
    fp = fopen(file_name, "rb");

    if(fp == NULL) {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    if(fseek(fp, sizeof(WavHeader), SEEK_SET) != 0) {
        fprintf(stderr, "\nError seeking location in file\n");
        exit(1);
    }


    int items_read = fread(buffer, sizeof(int16_t), samples, fp);
    
    if(ferror(fp)) {
        fprintf(stderr, "\nError reading from file\n");
        exit(1);
    }

    if(feof(fp)) {
        fprintf(stderr, "\nError closing file\n");
        exit(1);
    }

    fclose(fp);
    return 0;
}