#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void pad_buffer(
    int16_t* input, 
    int input_len, 
    int a_len, 
    int b_len,
    int16_t* output
) {
    
    for(int i=0; i<b_len; i++) {
        output[i] = 0;
    }

    for(int i=b_len; i<b_len+input_len; i++) {
        output[i] = input[i-b_len];
    }

    for(int i=b_len+input_len; i<b_len+input_len+a_len; i++) {
        output[i] = 0;
    }
}

void filter(
    float a[],
    int a_len,
    float b[],
    int b_len,
    int16_t* x,
    int x_len
) {
    int pad_len = b_len + x_len + a_len;
    int16_t* t = (int16_t*)malloc(pad_len * sizeof(int16_t));
    
    pad_buffer(x, x_len, a_len, b_len, t);

    for(int i=b_len; i<pad_len-a_len; i++) {
        t[i] = a[0]*t[i] + a[1]*t[i+1] + a[2]*t[i+2] - b[0]*t[i-1] - b[1]*t[i-2] - b[2]*t[i-3] - b[3]*t[i-4];
        x[i-b_len] = t[i];
    }



    free(t);
}
