#ifndef GENERATE_SIGNAL_H
#define GENERATE_SIGNAL_H

#include <stdint.h>
#include "sig_descriptor.h"
#define PI 3.14159265

void generateSignal(
    SigDescriptor s,
    int16_t *buffer
);

#endif