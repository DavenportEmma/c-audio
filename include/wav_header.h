#ifndef WAV_HEADER_H
#define WAV_HEADER_H

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
} WavHeader;

#endif