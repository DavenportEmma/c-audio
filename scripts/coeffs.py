import scipy as scipy
import argparse

def main(args):
    nyquist = args.fs/2

    wn = args.fc/nyquist
    print(scipy.signal.iirfilter(
        args.n,
        wn,
        btype=args.t
    ))
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
        type=int
    )

    parser.add_argument(
        '-t',
        type=str
    )

    args = parser.parse_args()
    main(args)