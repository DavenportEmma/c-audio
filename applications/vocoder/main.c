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

    FILE *carrier_fp;
    carrier_fp = fopen("audio/untitled.wav", "rb");
    flag = fseek(carrier_fp, sizeof(WavHeader), SEEK_SET);

    FILE *signal_fp;
    WavHeader *h_in = (WavHeader*)malloc(sizeof(WavHeader));
    signal_fp = fopen("audio/voice.wav", "rb");
    fread(h_in, sizeof(WavHeader), 1, signal_fp);

    if(flag) {
        fprintf(stderr, "Error initialising audio stream\n");
        exit(1);
    }

    FILE *out;
    out = fopen("build-vocoder/a.wav", "wb");
    WavHeader h = compileHeader(h_in->data_len / h_in->total_bytes_per_sample, 1, 44100, 16);
    fwrite(&h, sizeof(h), 1, out);

    // allocate memory for carrier and signal audio data
    int16_t* carrier_sample = (int16_t*)malloc(sizeof(int16_t));
    int16_t* signal_sample = (int16_t*)malloc(sizeof(int16_t));

    // allocate memory for filter buffers to store input and output samples
    FilterBuffer* c_buff_arr = (FilterBuffer*)calloc(NUM_BANDS, sizeof(FilterBuffer));
    FilterBuffer* s_buff_arr = (FilterBuffer*)calloc(NUM_BANDS, sizeof(FilterBuffer));
    FilterBuffer* env_buff_arr = (FilterBuffer*)calloc(NUM_BANDS, sizeof(FilterBuffer));

    // describe lowpass filter for envelope generator
    FilterDescriptor lp = {
        {1, -1.99597018, 0.99597828,0,0},
        {2.02585370e-06, 4.05170741e-06, 2.02585370e-06,0,0},
    };

    while(feof(carrier_fp) == 0 && feof(signal_fp) == 0) {        
        fread(carrier_sample, sizeof(int16_t), 1, carrier_fp);
        fread(signal_sample, sizeof(int16_t), 1, signal_fp);

        float modulated_sample = 0;

        for(int i = 0; i < NUM_BANDS; i++) {
            // get current filter coefficients from config.h
            FilterDescriptor* fd = &f_arr[i];
            FilterBuffer* carrier_buff = &c_buff_arr[i];
            FilterBuffer* signal_buff = &s_buff_arr[i];
            FilterBuffer* env_buff = &env_buff_arr[i];

            float carrier_out = 0;
            float signal_out = 0;

            for(int x = B_LEN - 1; x > 0; x--) {
                // shift input data buffer for bandpass stage
                carrier_buff->x[x] = carrier_buff->x[x-1];
                signal_buff->x[x] = signal_buff->x[x-1];

                // multiply data by coeff and update output
                carrier_out += carrier_buff->x[x] * fd->b[x];  
                signal_out += signal_buff->x[x] * fd->b[x];
            }

            // read new data into buffer
            carrier_buff->x[0] = *carrier_sample;
            signal_buff->x[0] = *signal_sample;

            carrier_out += carrier_buff->x[0] * fd->b[0];
            signal_out += signal_buff->x[0] * fd->b[0];
            
            for(int y = A_LEN - 1; y > 0; y--) {
                // shift output data buffer
                carrier_buff->y[y] = carrier_buff->y[y-1];
                signal_buff->y[y] = signal_buff->y[y-1];

                // multiple data by coeff and update output
                carrier_out -= carrier_buff->y[y] * fd->a[y];
                signal_out -= signal_buff->y[y] * fd->a[y];
            }

            // read new data into buffer
            carrier_buff->y[0] = carrier_out;
            signal_buff->y[0] = signal_out;

    /**************************************************************************/
    /*                   envelope generator                                   */
    /**************************************************************************/

            float env_out = 0;

            for(int x = B_LEN - 1; x > 0; x--) {
                env_buff->x[x] = env_buff->x[x-1];
                env_out += env_buff->x[x] * lp.b[x];  
            }

            env_buff->x[0] = fabs(signal_out) * 10;
            env_out += env_buff->x[0] * lp.b[0];
            
            for(int y = A_LEN - 1; y > 0; y--) {
                env_buff->y[y] = env_buff->y[y-1];
                env_out -= env_buff->y[y] * lp.a[y];
            }

            env_buff->y[0] = env_out;

            float max_signed = pow(2, 16) / 2;
            float sample_gain = env_out/max_signed;
            float modulated_band = carrier_out * sample_gain;

            modulated_sample += modulated_band;
        }

        int16_t o = (int16_t)modulated_sample * 5;
        int16_t* ptr = &o;
        fwrite(ptr, sizeof(int16_t), 1, out);
    }

    printf("Closing files\n");
    free(carrier_sample);
    free(signal_sample);
    free(h_in);
    free(c_buff_arr);
    free(s_buff_arr);
    free(env_buff_arr);
    fclose(out);
    fclose(carrier_fp);
    fclose(signal_fp);

    return 0;
}