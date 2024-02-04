from scipy.signal import butter, freqz
import matplotlib.pyplot as plt
import numpy as np
import argparse
import math

def main():
    fs = 44100
    b_arr = [4.1457715057178355e-06,0.0,-8.291543011435671e-06,0.0,4.1457715057178355e-06]
    # for b in args.b:
    #     b_arr.append(float(b))

    a_arr = [1.0,-3.9942315055923037,5.982712304250304,-3.9827300882648937,0.9942492896072537]
    # for a in args.a:
    #     a_arr.append(float(a))

    # Compute the frequency response
    w, h = freqz(b_arr, a_arr, worN=8000)
    frequencies = (fs * 0.5 / np.pi) * w

    # Plot the frequency response
    plt.figure()
    plt.plot(frequencies, 20 * np.log10(abs(h)))
    plt.title("Butterworth Bandpass Filter Frequency Response")
    plt.xlabel("Frequency [Hz]")
    plt.ylabel("Gain [dB]")
    plt.grid()
    # plt.show()

    # Plot the poles of the filter in the z-plane
    plt.figure()

    real = np.real(np.roots(a_arr))
    imag = np.imag(np.roots(a_arr))

    for i in range(len(real)):
        print(math.sqrt(pow(real[i], 2) + pow(imag[i], 2)))

    plt.scatter(np.real(np.roots(a_arr)), np.imag(np.roots(a_arr)), marker='x', color='red')
    plt.title("Pole-Zero Plot of Butterworth Bandpass Filter")
    plt.xlabel("Real part")
    plt.ylabel("Imaginary part")
    plt.axhline(0, color='black', linestyle='--', linewidth=0.5)
    plt.axvline(0, color='black', linestyle='--', linewidth=0.5)
    plt.grid()
    # plt.show()

if __name__ == "__main__":
    main()
    # parser = argparse.ArgumentParser()

    # parser.add_argument(
    #     '-b',
    #     nargs='*'
    # )

    # parser.add_argument(
    #     '-a',
    #     nargs='*'
    # )

    # parser.add_argument(
    #     '-fs',
    #     type=int
    # )

    # args = parser.parse_args()
    # main(args)