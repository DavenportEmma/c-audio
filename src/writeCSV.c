#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "writeCSV.h"

int writeCSV(char* file_name, int16_t* data, int data_len) {
    FILE *fp;
    fp = fopen(file_name, "w");

    if (fp == NULL) {
        fprintf(stderr, "\nError opened file\n");
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