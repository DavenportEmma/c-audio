#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void filter(
    double a[],
    int a_len,
    double b[],
    int b_len,
    int16_t* x,
    int x_len,
    int16_t* filtered
) {
    for(int i = 0; i < x_len; i++) {
        double a1, a2, b1, b2, b3 = 0;
        if(i >= 1) {
            a1 = a[1]*x[i-1];
            b1 = b[1]*filtered[i-1];
        }

        if(i >= 2) {
            a2 = a[2]*x[i-2];
            b2 = b[2]*filtered[i-2];
        }

        if(i >= 3) {
            b3 = b[3]*filtered[i-3];
        }


        filtered[i] = a[0]*x[0] + a1 + a2 - b1 - b2 - b3;
    }
}
