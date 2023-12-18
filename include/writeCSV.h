#ifndef WRITE_CSV_H
#define WRITE_CSV_H

#include <stdint.h>

int writeCSV(
    char* file_name,
    int16_t* data,
    int data_len
);

int writeCSV_uint8(
    char* file_name,
    uint8_t* data,
    int data_len
);


int writeCSV_normalised(
    char* file_name,
    float* data,
    int data_len
);

#endif
