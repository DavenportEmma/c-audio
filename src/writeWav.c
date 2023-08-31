#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "wav_header.h"
#include "writeWav.h"

int writeWav(WavHeader* h, char* file_name, int16_t* data) {
    printf("%s", file_name);
};