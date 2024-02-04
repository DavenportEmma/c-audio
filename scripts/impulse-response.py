import numpy as np
import matplotlib.pyplot as plt

# Given filter coefficients
a=[1.0,-3.989758216482782,5.972530620705377,-3.9757701351223256,0.9930003190141263]
b=[6.145989494088036e-06,0.0,-1.2291978988176072e-05,0.0,6.145989494088036e-06]

# Function to generate impulse response
def impulse_response(b, a, n=10000):
    impulse = np.zeros(n)
    impulse[0] = 1  # Impulse signal
    h = np.zeros(n)
    for i in range(n):
        for j in range(len(b)):
            if i - j >= 0:
                h[i] += b[j] * impulse[i - j]
        for k in range(1, len(a)):
            if i - k >= 0:
                h[i] -= a[k] * h[i - k]
    return h

# Calculate impulse response
impulse_response = impulse_response(b, a)

# Plot the impulse response
plt.figure(figsize=(8, 6))
plt.stem(np.arange(len(impulse_response)), impulse_response, use_line_collection=True)
plt.xlabel('Time')
plt.ylabel('Amplitude')
plt.title('Impulse Response of the Digital Filter')
plt.grid(True)
plt.show()
