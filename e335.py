# Looking at the first ten values, M(2^k+1) = 4^k-3^k+2^(k+1)
mod, phi, N = 7**9, 6*7**8, 10**18
def M(k): return (pow(4, k, mod) - pow(3, k, mod) + pow(2, k+1, mod)) % mod
print sum([M(k) * ((N-k)/phi+1) for k in xrange(phi)]) % mod
