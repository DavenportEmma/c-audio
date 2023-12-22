import argparse
import os
from math import log10
from coeffs import getCoeffs

def mel(f):
    return 2595 * log10(1 + (f/700))

def freq(m):
    return 700 * (pow(10, (m/2595)) - 1)

def coeffs(num_bands, spread, passband):
    coeffs = []
    for i in range(num_bands):
        m_centre = spread * i
        mc0 = m_centre - passband
        fc0 = freq(mc0)
        if(fc0 < 0):
            fc0 = 1

        mc1 = m_centre + passband
        fc1 = freq(mc1)

        coeffs.append(getCoeffs(
            2,
            44100,
            [fc0, fc1],
            "bandpass"
        ))

    return coeffs
def compileFilterDescriptor(coeffs_arr):
    cs = "\nFilterDescriptor f_arr[NUM_BANDS] = {\n"

    for f in coeffs_arr:
        cs += "\t{\n"       # start FilterDescriptor
        cs += "\t\t{"       # start a coefficients      
        for a in f['a']:
            cs += f"{a},"
        cs += "},\n"        # finish a coefficients

        cs += "\t\t{"       # start b coefficients
        for b in f['b']:
            cs += f"{b},"
        cs += "},\n"         # finish b coefficients
        
        cs += "\t},\n"

    cs += "};"
    return cs

def main(args):
    num_bands = 40
    f_max = 12000
    m_max = mel(f_max)

    spread = m_max / num_bands

    passband = spread/2 - 20

    coeffs_arr = coeffs(num_bands, spread, passband)
    
    if(not os.path.isdir(args.b)):
        os.mkdir(args.b)

    with open(f"{args.b}/config.h", 'w') as f:
        a_len = len(coeffs_arr[0]['a'])
        b_len = len(coeffs_arr[0]['b'])
        f.write(f"""#ifndef CONFIG_H
#define CONFIG_H
#define A_LEN {a_len}
#define B_LEN {b_len}
#define NUM_BANDS {num_bands}
#include "filter_descriptor.h"
""")
        f.write(compileFilterDescriptor(coeffs_arr))

        f.write("\n#endif")

    return 0

if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument(
        '-b',
        type=str,
        help="build directory"
    )

    parser.add_argument(
        '-n',
        type=int,
        help='number of filters'
    )
    
    args = parser.parse_args()
    main(args)