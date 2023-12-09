#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "readWav.h"
#include "wav_header.h"
#include "generateSignal.h"
#include "writeWav.h"
#include "writeCSV.h"

int main(int argc, char** argv) {
    /*
        how to get envelope
        1. abs on signal
        2. apply low pass (Fc ~10Hz)
        3. BAM
    */

    WavHeader *h = (WavHeader*)malloc(sizeof(WavHeader));

    int flag = getMetadata("audio/AM.wav", h);

    // printf("file_type %s\n", h->file_type);
    // printf("file_size %i\n", h->file_size);
    // printf("file_type_header %s\n", h->file_type_header);
    // printf("format_chunk_marker %s\n", h->format_chunk_marker);
    // printf("format_data_len %i\n", h->format_data_len);
    // printf("format_type %i\n", h->format_type);
    // printf("num_channels %i\n", h->num_channels);
    // printf("sample_rate %i\n", h->sample_rate);
    // printf("byte_rate %i\n", h->byte_rate);
    // printf("total_bytes_per_sample %i\n", h->total_bytes_per_sample);
    // printf("bits_per_sample %i\n", h->bits_per_sample);
    // printf("data_start %s\n", h->data_start);
    // printf("data_len %i\n", h->data_len);

    int8_t* buffer = (int8_t*)malloc(h->data_len);

    extractAudioData("audio/AM.wav", h, buffer, h->data_len);

    int16_t* buffer2 = (int16_t*)malloc(h->data_len * 2);

    for(int i = 0; i < h->data_len; i++) {
        buffer2[i] = (int16_t)buffer[i];
        printf("%i\n", buffer2[i]);
    }

    writeCSV("build-envelope-detection/a.txt", buffer2, h->data_len);

    free(buffer);
    free(buffer2);
    return 0;
}