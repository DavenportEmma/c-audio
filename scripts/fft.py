import matplotlib.pyplot as plt
from scipy.fftpack import fft
from scipy.io import wavfile # get the api
fs, data = wavfile.read('out/a.out.wav') # load the data
a = data.T # this is a two channel soundtrack, I get the first track
b=[(ele/2**16.)*2-1 for ele in a] # this is 8-bit track, b is now normalized on [-1,1)
c = fft(b) # calculate fourier transform (complex numbers list)
d = int(len(c)/2)  # you only need half of the fft list (real signal symmetry)
c[0] = 0
plt.plot(abs(c[:(d-1)]),'r')
plt.show()