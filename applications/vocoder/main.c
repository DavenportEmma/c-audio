#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "config.h"
#include "filter_descriptor.h"
#include "wav_header.h"
#include "readWav.h"

WavHeader compileHeader(
    int samples, 
    short int num_channels, 
    int sample_rate, 
    short int bits_per_sample
) {
    int byte_rate = sample_rate * bits_per_sample * num_channels / 8;
    short int bytes_per_sample = bits_per_sample / 8; // 2 for 16b mono

    WavHeader h = {
        "RIFF",
        36,
        "WAVE",
        "fmt\x20", //  \x20 represents the end of header
        16,
        1,
        num_channels,
        sample_rate,
        byte_rate,
        bytes_per_sample,
        bits_per_sample,
        "data",
        samples * bytes_per_sample
    };

    return h;
}

int main(int argc, char** argv) {
    int flag = 0;

    FILE *carrier;
    carrier = fopen("audio/untitled.wav", "rb");
    flag = fseek(carrier, sizeof(WavHeader), SEEK_SET);

    FILE *signal;
    WavHeader *h_in = (WavHeader*)malloc(sizeof(WavHeader));
    signal = fopen("audio/voice.wav", "rb");
    fread(h_in, sizeof(WavHeader), 1, signal);

    if(flag) {
        fprintf(stderr, "Error initialising audio stream\n");
        exit(1);
    }

    FILE *out;
    out = fopen("build-vocoder/a.wav", "wb");
    WavHeader h = compileHeader(h_in->data_len / h_in->total_bytes_per_sample, 1, 44100, 16);
    fwrite(&h, sizeof(h), 1, out);

    // allocate memory for carrier and signal audio data
    int16_t* c = (int16_t*)malloc(sizeof(int16_t));
    int16_t* s = (int16_t*)malloc(sizeof(int16_t));

    // allocate memory for filter buffers
    FilterBuffer* c_buff_arr = (FilterBuffer*)calloc(NUM_BANDS, sizeof(FilterBuffer));
    FilterBuffer* s_buff_arr = (FilterBuffer*)calloc(NUM_BANDS, sizeof(FilterBuffer));
    FilterBuffer* env_buff_arr = (FilterBuffer*)calloc(NUM_BANDS, sizeof(FilterBuffer));

    // describe lowpass filter for envelope generator
    FilterDescriptor lp = {
        {1, -1.99597018, 0.99597828,0,0},
        {2.02585370e-06, 4.05170741e-06, 2.02585370e-06,0,0},
    };

    while(feof(carrier) == 0 && feof(signal) == 0) {        
        fread(c, sizeof(int16_t), 1, carrier);
        fread(s, sizeof(int16_t), 1, signal);

        float modulated_sample = 0;

        for(int i = 0; i < NUM_BANDS; i++) {
            FilterDescriptor* fd = &f_arr[i];
            FilterBuffer* c_buff = &c_buff_arr[i];
            FilterBuffer* s_buff = &s_buff_arr[i];
            FilterBuffer* env_buff = &env_buff_arr[i];

            float yc = 0;
            float ys = 0;

            for(int x = B_LEN - 1; x > 0; x--) {
                // shift input data buffer for bandpass stage
                c_buff->x[x] = c_buff->x[x-1];
                s_buff->x[x] = s_buff->x[x-1];

                // multiply data by coeff and update output
                yc += c_buff->x[x] * fd->b[x];  
                ys += s_buff->x[x] * fd->b[x];
            }

            // read new data into buffer
            c_buff->x[0] = *c;
            s_buff->x[0] = *s;

            yc += c_buff->x[0] * fd->b[0];
            ys += s_buff->x[0] * fd->b[0];
            
            for(int y = A_LEN - 1; y > 0; y--) {
                // shift output data buffer
                c_buff->y[y] = c_buff->y[y-1];
                s_buff->y[y] = s_buff->y[y-1];

                // multiple data by coeff and update output
                yc -= c_buff->y[y] * fd->a[y];
                ys -= s_buff->y[y] * fd->a[y];
            }

            // read new data into buffer
            c_buff->y[0] = yc;
            s_buff->y[0] = ys;

    /**************************************************************************/
    /*                   envelope generator                                   */
    /**************************************************************************/

            float yenv = 0;

            for(int x = B_LEN - 1; x > 0; x--) {
                env_buff->x[x] = env_buff->x[x-1];
                yenv += env_buff->x[x] * lp.b[x];  
            }

            env_buff->x[0] = fabs(ys) * 10;
            yenv += env_buff->x[0] * lp.b[0];
            
            for(int y = A_LEN - 1; y > 0; y--) {
                env_buff->y[y] = env_buff->y[y-1];
                yenv -= env_buff->y[y] * lp.a[y];
            }

            env_buff->y[0] = yenv;

            float max_signed = pow(2, 16) / 2;
            float sample_gain = yenv/max_signed;
            float modulated_band = yc * sample_gain;

            modulated_sample += modulated_band;
        }

        int16_t o = (int16_t)modulated_sample * 5;
        int16_t* ptr = &o;
        fwrite(ptr, sizeof(int16_t), 1, out);
    }

    printf("Closing files\n");
    free(c);
    free(s);
    free(h_in);
    free(c_buff_arr);
    free(s_buff_arr);
    free(env_buff_arr);
    fclose(out);
    fclose(carrier);
    fclose(signal);

    return 0;
}