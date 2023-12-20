#ifndef READ_WAV_H
#define READ_WAV_H

#include <stdint.h>
#include "wav_header.h"

int getMetadata(
    char* file_name,
    WavHeader* h
);

int extractAudioData(
    char* file_name,
    int16_t* buffer,
    int buffer_len
);

#endif
