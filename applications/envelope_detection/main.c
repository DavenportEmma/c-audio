#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "readWav.h"
#include "wav_header.h"
#include "generateSignal.h"
#include "writeWav.h"

int main(int argc, char** argv) {
    /*
        how to get envelope
        1. abs on signal
        2. apply low pass (Fc ~10Hz)
        3. BAM
    */

    WavHeader *h = (WavHeader*)malloc(sizeof(WavHeader));

    int flag = getMetadata("audio/AM.wav", h);

    printf("file_type %s\n", h->file_type);
    printf("file_size %i\n", h->file_size);
    printf("file_type_header %s\n", h->file_type_header);
    printf("format_chunk_marker %s\n", h->format_chunk_marker);
    printf("format_data_len %i\n", h->format_data_len);
    printf("format_type %i\n", h->format_type);
    printf("num_channels %i\n", h->num_channels);
    printf("sample_rate %i\n", h->sample_rate);
    printf("byte_rate %i\n", h->byte_rate);
    printf("total_bytes_per_sample %i\n", h->total_bytes_per_sample);
    printf("bits_per_sample %i\n", h->bits_per_sample);
    printf("data_start %s\n", h->data_start);
    printf("data_len %i\n", h->data_len);

    int16_t* buffer = (int16_t*)malloc(h->total_bytes_per_sample*h->data_len);
    
    extractAudioData("audio/AM.wav", h, buffer, h->data_len);

    for(int i = 0; i < h->data_len; i++) {
        printf("%i\n", buffer[i]);
    }

    free(buffer);

    // SigDescriptor s = {
    //     h->sample_rate,
    //     100,
    //     h->data_len,
    //     10000,
    //     0,
    //     0,
    //     SINE
    // };

    // int16_t* dt = (int16_t*)malloc(sizeof(int16_t)*h->data_len);
    // generateSignal(s, dt);

    // short int num_channels = 1;
    // int sample_rate = h->sample_rate;
    // short int bits_per_sample = 16;
    // int byte_rate = sample_rate * bits_per_sample * num_channels / 8;
    // short int bytes_per_sample = bits_per_sample / 8; // 2 for 16b mono

    // WavHeader h2 = {
    //     "RIFF",
    //     36,
    //     "WAVE",
    //     "fmt\x20", //  \x20 represents the end of header
    //     16,
    //     1,
    //     num_channels,
    //     sample_rate,
    //     byte_rate,
    //     bytes_per_sample,
    //     bits_per_sample,
    //     "data",
    //     h->data_len * bytes_per_sample
    // };

    // writeWav(h2, "build-env_det/a.wav", dt, h->data_len);
    // free(dt);

    return 0;
}