#ifndef WRITE_WAV_H
#define WRITE_WAV_H

#include <stdint.h>

#include "wav_header.h"

int writeWav(
    WavHeader* h,
    char* file_name,
    int16_t* data
);

#endif
