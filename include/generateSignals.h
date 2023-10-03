#ifndef GENERATE_SIGNALS_H
#define GENERATE_SIGNALS_H

#include <stdint.h>
#include "sig_descriptor.h"
#include "wav_header.h"
#define PI 3.14159265

void generateSignals(
    WavHeader h,
    SigDescriptor s[],
    int num_sigs,
    int16_t* buffer
);

#endif