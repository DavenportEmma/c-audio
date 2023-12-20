#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "writeCSV.h"

int writeCSV(char* file_name, int16_t* data, int data_len) {
    FILE *fp;
    fp = fopen(file_name, "wb");

    if (fp == NULL) {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    int flag = 0;

    for(int i=0; i<data_len; i++) {
        fprintf(fp, "%i\n", data[i]);
    }
 
    // close file
    fclose(fp);

    return 0;
};


int writeCSV_normalised(char *file_name, float* data, int data_len) {
    FILE *fp;
    fp = fopen(file_name, "wb");

    if (fp == NULL) {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    int flag = 0;

    for(int i=0; i<data_len; i++) {
        flag = fprintf(fp, "%f\n", data[i]);
        if(flag < 0) {
            printf("error\n");
        }
    }
 
    // close file
    fclose(fp);

    return 0;
}