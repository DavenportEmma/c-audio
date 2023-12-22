import scipy as scipy
import argparse

def getCoeffs(n, fs, fc, t):
    nyquist = fs/2

    wn = []

    for fc in fc:
        wn.append(fc/nyquist)

    coeffs = scipy.signal.iirfilter(
        n,
        wn,
        btype=t
    )

    return {
        'b': coeffs[0],
        'a': coeffs[1]
    }

def main(args):
    getCoeffs(
        args.n,
        args.fs,
        args.fc,
        args.t
    )
    return 0

if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument(
        '-n',
        type=int
    )

    parser.add_argument(
        '-fs',
        type=int
    )

    parser.add_argument(
        '-fc',
        type=int,
        nargs='*'
    )

    parser.add_argument(
        '-t',
        type=str
    )

    args = parser.parse_args()
    main(args)