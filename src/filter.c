#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "filter.h"

void pad_buffer(int16_t* input, int16_t* output, int len) {
    for(int i=0; i<len; i++) {
        if(i < B_COEFFS) {
            output[i] = 0;
        } else if(i >= B_COEFFS && i < (len-A_COEFFS)) {
            output[i] = input[i-B_COEFFS];
        } else {
            output[i] = 0;
        }
    }
}

void filter(
    FilterDescriptor f,
    int16_t* d,
    int d_len
) {
    // int pad_len = B_COEFFS + d_len + A_COEFFS;
    float* t = (float*)calloc(0, d_len * sizeof(float));
    
    // pad_buffer(x, t, pad_len);

    
    for(int i=0; i<d_len; i++) {
        int xn = d[i];
        int xn1 = (i >= 1 ? d[i-1] : 0);
        int xn2 = (i >= 2 ? d[i-2] : 0);
        int xn3 = (i >= 3 ? d[i-3] : 0);

        int tn1 = (i >= 1 ? t[i-1] : 0);
        int tn2 = (i >= 2 ? t[i-2] : 0);
        int tn3 = (i >= 3 ? t[i-3] : 0);

        float a0 = f.a[0];
        float a1 = f.a[1];
        float a2 = f.a[2];
        float a3 = f.a[3];

        float b0 = f.b[0];
        float b1 = f.b[1];
        float b2 = f.b[2];
        float b3 = f.b[3];

        t[i] = xn*a0 + xn1*a1;
        printf("%f\n", t[i]);
    }

    free(t);
}
