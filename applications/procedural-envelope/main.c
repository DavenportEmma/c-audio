#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "wav_header.h"

int main(int argc, char** argv) {
    int flag;
    
    FILE *carrier;
    carrier = fopen("audio/fadeout.wav", "rb");
    flag = fseek(carrier, sizeof(WavHeader), SEEK_SET);

    FILE *signal;
    signal = fopen("audio/200hz.wav", "rb");
    flag = fseek(signal, sizeof(WavHeader), SEEK_SET);

    if(flag) {
        fprintf(stderr, "Error initialising audio files\n");
        exit(1);
    }

    int16_t* c_buff = (int16_t*)malloc(sizeof(int16_t));
    int16_t* s_buff = (int16_t*)malloc(sizeof(int16_t));

    // filter stuff
    #define A_LEN 3
    #define B_LEN 3
    float a_coeff[A_LEN] = {1, -1.99597018, 0.99597828};
    float b_coeff[B_LEN] = {2.02585370e-06, 4.05170741e-06, 2.02585370e-06};
    float* x_buff = (float*)calloc(A_LEN, sizeof(float));
    float* y_buff = (float*)calloc(B_LEN, sizeof(float));
    
    FILE *fp;
    fp = fopen("build-procedural-envelope/a.wav", "wb");

    int samples = 176400;
    short int num_channels = 1;
    int sample_rate = 44100;
    short int bits_per_sample = 16;
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

    fwrite(&h, sizeof(h), 1, fp);


    while(feof(carrier) == 0 || feof(signal) == 0) {
        fread(c_buff, sizeof(int16_t), 1, carrier);
        // envelope detection step 1: get absolute value of signal
        int16_t abs_c = abs(c_buff[0]);

        // shift all elements of the filter input buffer one to the right
        x_buff[2] = x_buff[1];
        x_buff[1] = x_buff[0];
        x_buff[0] = abs_c;

        y_buff[2] = y_buff[1];
        y_buff[1] = y_buff[0];

        float b0 = x_buff[0]*b_coeff[0];
        float b1 = x_buff[1]*b_coeff[1];
        float b2 = x_buff[2]*b_coeff[2];

        float a1 = y_buff[1]*a_coeff[1];
        float a2 = y_buff[2]*a_coeff[2];

        // envelope step 2: apply low pass filter to rectified signal
        y_buff[0] = b0 + b1 + b2 - a1 - a2;

        // max value of a signed 16 bit int
        float max_signed = pow(2, 16) / 2;
        // normalise filter output from 0 -> 1
        float sample_gain = y_buff[0]/max_signed;

        fread(s_buff, sizeof(int16_t), 1, signal);

        int16_t s_norm = s_buff[0] * sample_gain;
        int16_t* ptr = &s_norm;
        fwrite(ptr, sizeof(s_norm), 1, fp);
    }

    printf("Closing files\n");
    free(c_buff);
    free(s_buff);
    free(x_buff);
    free(y_buff);
    fclose(carrier);
    fclose(signal);
    fclose(fp);

    return 0;
}