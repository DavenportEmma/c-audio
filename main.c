#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    typedef struct {
        char file_type[4]; // RIFF
        int file_size;
        char file_type_header[4]; // WAVE
        char format_chunk_marker[4]; // fmt
        int format_data_len; // length of format data as listed above
        short int format_type; // 1
        short int num_channels; // 2
        int sample_rate; // 44100
        int byte_rate; // sample rate * bits/sample * channels / 8
        // 4410khz * 16 bits per sample * 1 channel / 8 bits per byte
        short int total_bytes_per_sample; // 2 for 16 bit mono 
        short int bits_per_sample; // 16
        char data_start[4]; // data
        int data_len; // size of the data section
    } header;

    header h = {
        "RIFF",
        36,
        "WAVE",
        "fmt\x20", //  \x20 represents the end of header
        16,
        1,
        1,
        44100,
        176400,
        4,
        16,
        "data",
        0
    };

    FILE *fp;
    fp = fopen("a.wav", "w");

    if (fp == NULL) {
        fprintf(stderr, "\nError opened file\n");
        exit(1);
    }

    int flag = 0;
    flag = fwrite(&h, sizeof(header), 1, fp);

    int16_t d[] = {
    0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,
    0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,
    0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,
    0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,
    0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,
    0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,
    0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,
    0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,
    0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,
    0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,0x8FFF,
    };

    flag = fwrite(&d, sizeof(d), 1, fp);

    if (flag) {
        printf("Contents of the structure written "
               "successfully");
    }
    else
        printf("Error Writing to File!");
 
    // close file
    fclose(fp);

    return 0;
}