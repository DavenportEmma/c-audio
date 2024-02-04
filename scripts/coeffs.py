import scipy as scipy

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