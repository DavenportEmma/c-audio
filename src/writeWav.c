#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "wav_header.h"
#include "writeWav.h"

int writeWav(WavHeader header, char* file_name, int16_t* data, int data_len) {
    FILE *fp;
    fp = fopen(file_name, "wb");

    if (fp == NULL) {
        fprintf(stderr, "\nError opened file\n");
        exit(1);
    }

    int flag = 0;
    flag = fwrite(&header, sizeof(header), 1, fp);

    flag = fwrite(data, sizeof(int16_t), data_len, fp);

    if (flag) {
        printf("Contents of the structure written "
               "successfully");
    }
    else
        printf("Error Writing to File!");
 
    // close file
    fclose(fp);

    return 0;
};