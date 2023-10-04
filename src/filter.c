#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "filter.h"

void filter(
    FilterDescriptor f,
    int16_t* d,
    int16_t* o,
    int len
) {
    double* temp = (double*)calloc(len, len * sizeof(double));

    for(int i=0; i<len; i++) {
        int xn = d[i];
        int xn1 = (i >= 1 ? d[i-1] : 0);
        int xn2 = (i >= 2 ? d[i-2] : 0);
        int xn3 = (i >= 3 ? d[i-3] : 0);

        double tn1 = (i >= 1 ? temp[i-1] : 0);
        double tn2 = (i >= 2 ? temp[i-2] : 0);
        double tn3 = (i >= 3 ? temp[i-3] : 0);

        double a0 = f.a[0];
        double a1 = f.a[1];
        double a2 = f.a[2];
        double a3 = f.a[3];

        double b0 = f.b[0];
        double b1 = f.b[1];
        double b2 = f.b[2];
        double b3 = f.b[3];

        temp[i] = xn*a0 + xn1*a1 + xn2*a2 + xn3*a3 - tn1*b1 - tn2*b2 - tn3*b3;
        o[i] = (int16_t)temp[i];
    }

    free(temp);
}
