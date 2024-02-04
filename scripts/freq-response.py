import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import freqz

# Replace these with your filter coefficients
a=[1.0,-3.989758216482782,5.972530620705377,-3.9757701351223256,0.9930003190141263]
b=[6.145989494088036e-06,0.0,-1.2291978988176072e-05,0.0,6.145989494088036e-06]

# Compute frequency response
w, h = freqz(b, a)

# Magnitude response in dB
magnitude_db = 20 * np.log10(abs(h))

# Phase response in radians
phase = np.angle(h)

# Frequency in Hz (assuming normalized digital frequency)
sampling_frequency = 44100  # Replace this with your sampling frequency
frequency = w * (sampling_frequency / (2 * np.pi))

# Plot magnitude response
plt.figure(figsize=(10, 6))
plt.subplot(2, 1, 1)
plt.plot(frequency, magnitude_db, 'b')
plt.title('Frequency Response')
plt.ylabel('Magnitude (dB)')
plt.xlabel('Frequency (Hz)')
plt.grid()

# Plot phase response
plt.subplot(2, 1, 2)
plt.plot(frequency, phase, 'r')
plt.ylabel('Phase (radians)')
plt.xlabel('Frequency (Hz)')
plt.grid()

plt.tight_layout()
plt.show()
