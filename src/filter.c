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
    for(int i=0; i<len; i++) {
        int xn = d[i];
        int xn1 = (i >= 1 ? d[i-1] : 0);
        int xn2 = (i >= 2 ? d[i-2] : 0);
        int xn3 = (i >= 3 ? d[i-3] : 0);

        int tn1 = (i >= 1 ? o[i-1] : 0);
        int tn2 = (i >= 2 ? o[i-2] : 0);
        int tn3 = (i >= 3 ? o[i-3] : 0);

        float a0 = f.a[0];
        float a1 = f.a[1];
        float a2 = f.a[2];
        float a3 = f.a[3];

        float b0 = f.b[0];
        float b1 = f.b[1];
        float b2 = f.b[2];
        float b3 = f.b[3];

        o[i] = xn*a0 + xn1*a1 + xn2*a2 + xn3*a3 - tn1*b1 - tn2*b2 - tn3*b3;
    }
}
