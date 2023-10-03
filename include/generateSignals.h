#ifndef GENERATE_SIGNALS_H
#define GENERATE_SIGNALS_H

#include <stdint.h>
#include "sig_descriptor.h"
#include "wav_header.h"

void generateSignals(
    WavHeader h,
    SigDescriptor s[],
    int num_sigs,
    int16_t* buffer
);

#endif