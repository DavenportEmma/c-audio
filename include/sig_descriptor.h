#ifndef SIG_DESCRIPTOR_H
#define SIG_DESCRIPTOR_H

typedef enum {
    SINE,
    SQUARE
} SigType;

typedef struct {
    int sample_rate;
    int freq;
    int samples;
    int gain;
    int offset;
    float phase;
    SigType type;
} SigDescriptor;

#endif