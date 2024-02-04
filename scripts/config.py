import argparse
import os
from math import log10
from coeffs import getCoeffs

def mel(f):
    return 2595 * log10(1 + (f/700))

def freq(m):
    return 700 * (pow(10, (m/2595)) - 1)

def coeffs(num_bands, m_max, f_max, spread, order):
    coeffs = []
    for i in range(num_bands):
        m_centre = (m_max/num_bands) * (i + 1)

        mc0 = m_centre - spread
        mc1 = m_centre + spread

        fc0 = freq(mc0)
        fc1 = freq(mc1)

        print(fc0, fc1)

        # f_centre = freq(m_centre)
        # passband0 = mel(f_centre - spread)
        # passband1 = mel(f_centre + spread)

        # mc0 = m_centre - passband0
        # fc0 = freq(passband0)

        # mc1 = m_centre + passband1
        # fc1 = freq(passband1)

        coeffs.append(getCoeffs(
            order,
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

def config(args):
    num_bands = args.num_filters
    f_max = args.f_max
    m_max = mel(f_max)

    coeffs_arr = coeffs(num_bands, m_max, f_max, args.spread, args.filter_order)
    
    if(not os.path.isdir(args.build_dir)):
        os.mkdir(args.build_dir)

    with open(f"{args.build_dir}/config.h", 'w') as f:
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


def main(args):
    config(args)
    return 0

if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument(
        '-b',
        '--build-dir',
        type=str,
        help="build directory"
    )
    
    parser.add_argument(
        '-fm',
        '--f-max',
        type=int,
        help='max frequency'
    )

    parser.add_argument(
        '-s',
        '--spread',
        type=int,
        help='spread'
    )

    parser.add_argument(
        '-n',
        '--num-filters',
        type=int,
        help='number of filters'
    )

    parser.add_argument(
        '-o',
        '--filter-order',
        type=int,
        help='filter order'
    )

    args = parser.parse_args()
    main(args)